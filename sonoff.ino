#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include "config.h"
#include "wifi.h"
#include "webserver.h"
#include <DNSServer.h>
#include <ESP8266mDNS.h>

/**
   @brief mDNS and OTA Constants
   @{
*/
#define TelePiVersion "Ver: 1.2"
#define MQTT_SERVER "192.168.2.9"  // My mosquitto server
/// @}

#define max_variable 150  // Max variable length 
const byte DNS_PORT = 53;

WiFiClient wifiClient;
PubSubClient mqttClient;

Conf *configure;
TeWifi *tewifi;

TeWebServer *WebS;


// **********************************
// **       PROGRAM        **
// **********************************

const int GPIO00Button = 0;
const int GPIO01TX = 1;
const int GPIO03RX = 3;
const int GPIO12Relay = 12;
const int GPIO13Led = 13;
const int GPIO14Pin = 14;

int buttonState = HIGH;
int buttonStateOld = HIGH;


void blink(int gpionum, int one, int num) {
  int state = digitalRead(gpionum);
  for (int i = 0; i < num; i++) {
    digitalWrite(gpionum, HIGH);
    delay(one / 2);
    digitalWrite(gpionum, LOW);
    delay(one / 2);
  }
  digitalWrite(gpionum, state);
  return;
}

int filter(int input, int state, int dsec) {
  int i = 0, inc = 10; //Increment 50ms
  while (i < dsec) {
    delay(inc);
    i += inc;
    pinMode(input, INPUT_PULLUP);
    if (digitalRead(input) != state) return false;
  }
  return true;
}

int gpioI[15]={HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
int gpioO[15]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
int gpioP[15]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};


char message_buff[100];
char topic_buff[100];
void mqttmessage(int gpio,int value,String mytype) {
    if (!mqttClient.connected()) return;
    String pubString = "{\"report\":{\"light\": \"" + String(value) + "\"}}";
//    pubString.toCharArray(message_buff, pubString.length()+1);
    String topicString = "telepi/"+mytype+"/"+configure->getVariable("hostname")+"/"+String(gpio);
//    topicString.toCharArray(topic_buff, topicString.length()+1);
    if (mqttClient.publish(topicString.c_str(), pubString.c_str())==false) {
//        mqttClient = PubSubClient(MQTT_SERVER, 1883, callback,wifiClient);
        mqttClient.connect(tewifi->hostname.c_str(),"admin","<kitipasa>");
    }
}

bool changeOUT(int gpioout) {
   if (gpioO[gpioout]==LOW) 
      changeOUT_ON(gpioout);
   else 
      changeOUT_OFF(gpioout);
}
bool changeOUT_ON(int gpioout) {
         gpioO[gpioout]=HIGH;
         pinMode(gpioout, OUTPUT);
         digitalWrite(gpioout,HIGH);
         mqttmessage(gpioout,gpioO[gpioout],"Relay");
         if (configure->getVariable("gpio13")=="Relay") digitalWrite(GPIO13Led, LOW);
         if (configure->getVariable("gpio13")=="Pulse") {
            digitalWrite(GPIO13Led, LOW);
            delay(500);
            digitalWrite(GPIO13Led, HIGH);
         }
         return true;
}
bool changeOUT_OFF(int gpioout) {
         gpioO[gpioout]=LOW;
         pinMode(gpioout, OUTPUT);
         digitalWrite(gpioout, LOW);
         mqttmessage(gpioout,gpioO[gpioout],"Relay");
         if (configure->getVariable("gpio13")=="Relay") digitalWrite(GPIO13Led, HIGH);
         if (configure->getVariable("gpio13")=="Pulse") {
            digitalWrite(GPIO13Led, LOW);
            delay(500);
            digitalWrite(GPIO13Led, HIGH);
         }
         return true;
}

bool dealwithgpio(int gpioin,int gpioout) {
   String gpiotxt=(gpioin<10?"gpio0":"gpio")+String(gpioin);
   String modew=configure->getVariable(gpiotxt);
   if (modew=="NU") return false;
   if (modew.startsWith("IN")) {  // IN and IN-R
     String modesw=configure->getVariable(gpiotxt+"sw");
     if (modesw=="push") {
       if (gpioP[gpioin]==LOW) {
         if (filter(gpioin, LOW, 50)) {
             if (modew=="IN-R") changeOUT(gpioout);
             gpioP[gpioin]=HIGH;
             mqttmessage(gpioin,gpioP[gpioin],"in");
         }
       } else {  
         if (filter(gpioin, HIGH, 100)) {
             gpioP[gpioin]=LOW;
             mqttmessage(gpioin,gpioP[gpioin],"in");
         }
       }
     }
     if (modesw=="switch") {
       if (filter(gpioin, (gpioI[gpioin]==LOW?HIGH:LOW), 100)) {
           gpioI[gpioin]= (gpioI[gpioin]==LOW?HIGH:LOW);
           if (modew=="IN-R") changeOUT(gpioout);
           mqttmessage(gpioin,gpioI[gpioin],"in");
       }
     }
   }
   if (modew=="OUT") {
         
   }
}

#define APDEFAULT 0
#define APFIXED 1
#define APSMARTCONF 2
int bootmode=APDEFAULT;

void setup(void) {
  pinMode(GPIO13Led, OUTPUT);
  blink(GPIO13Led, 300, 2);
  configure = new Conf();
  blink(GPIO13Led, 300, 2);
  tewifi = new TeWifi(configure);
  blink(GPIO13Led, 300, 2);
  // Go to Config on boot
  if (filter(GPIO00Button, LOW, 700)) { //Check if button is HIGH for ~700ms
    blink(GPIO13Led, 500, 8);
    if (filter(GPIO00Button, LOW, 700)) { //Check if button is HIGH for ~700ms
      blink(GPIO13Led, 250, 16);
//      configure->reset();
      tewifi->modeDefaultWifiAP();
      bootmode=APFIXED;
    } else {
      //WiFi.mode(WIFI_AP_STA);
      //delay(500);
      WiFi.beginSmartConfig();
      bootmode=APSMARTCONF;
      while(1){
         delay(1000);
         if(WiFi.smartConfigDone()){
            //Serial.println("SmartConfig Success");
            break;
         }
      }
    }
  } else {
    tewifi->modeWifiClient();
    bootmode=APDEFAULT;
  }

  pinMode(GPIO12Relay, OUTPUT);
  digitalWrite(GPIO12Relay, HIGH);

  pinMode(GPIO00Button, INPUT_PULLUP);

  WebS = new TeWebServer(80);

  // Start OTA server.
  ArduinoOTA.setHostname((const char *)tewifi->hostname.c_str());
  ArduinoOTA.begin();
  blink(GPIO13Led, 600, 3);
  
  if ( bootmode==APDEFAULT) {
    mqttClient = PubSubClient(MQTT_SERVER, 1883, callback,wifiClient);
    mqttClient.connect(tewifi->hostname.c_str(),"admin","<kitipasa>");
    String subscribeme="telepi/DEBUG/"+configure->getVariable("hostname")+"/BootIP";
    IPAddress ip=WiFi.localIP();
    String myip=String(ip[0])+"."+String(ip[1])+"."+String(ip[2])+"."+String(ip[3]);
    mqttClient.publish(subscribeme.c_str(), myip.c_str());
    
    subscribeme="telepi/Relay/OUT/"+configure->getVariable("hostname")+"/#";
    mqttClient.subscribe(subscribeme.c_str());
  }
  
}

void loop(void) {
 // tewifi->checkWifi();
  WebS->httpServer->handleClient();
  dealwithgpio(GPIO00Button,GPIO12Relay);
  dealwithgpio(GPIO14Pin,GPIO12Relay);
  dealwithgpio(GPIO03RX,GPIO12Relay);
  dealwithgpio(GPIO01TX,GPIO12Relay);

  if ( bootmode==APDEFAULT) mqttClient.loop(); 
  else {
    if (MDNS.begin(tewifi->hostname.c_str())) {
        MDNS.addService("esp", "tcp", 80); // Announce esp tcp service on port 8080
    }
  }

  ArduinoOTA.handle(); //  Handle OTA server.
  yield();

}

void callback(char* topic, byte* payload, unsigned int length) {
  int i = 0;
  // create character buffer with ending null terminator (string)
  for(i=0; i<length; i++) {
    message_buff[i] = payload[i];
  }  
  message_buff[i] = '\0';
  String msgString = String(message_buff);

  String topicString = "telepi/DEBUG/"+configure->getVariable("hostname")+"/RECEIVED";
  mqttClient.publish(topicString.c_str(), message_buff);

  if (msgString.equals("{\"command\":{\"relaymode\": \"OFF\"}}")) {
      changeOUT_OFF(GPIO12Relay);
  } else if (msgString.equals("{\"command\":{\"relaymode\": \"ON\"}}")) {
      changeOUT_ON(GPIO12Relay);
  } else if (msgString.equals("{\"command\":{\"relaymode\": \"SENSE\"}}")) {
    //senseMode = MODE_SENSE;
  } else {
      topicString = "telepi/DEBUG/"+configure->getVariable("hostname")+"/RECEIVED";
      mqttClient.publish(topicString.c_str(), msgString.c_str());
  }
}



