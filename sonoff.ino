#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include "config.h"
#include "wifi.h"
#include "webserver.h"

/**
   @brief mDNS and OTA Constants
   @{
*/
#define MQTT_SERVER "192.168.2.9"  // My mosquitto server
/// @}

#define max_variable 150  // Max variable length 
const byte DNS_PORT = 53;

WiFiClient wifiClient;
PubSubClient mqttClient;

Conf *configure;
TeWifi *tewifi;

TeWebServer *WebS;


// ******************************************************************************************************
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
    digitalWrite(gpionum, LOW);
    delay(one / 2);
    digitalWrite(gpionum, HIGH);
    delay(one / 2);
  }
  digitalWrite(gpionum, state);
  return;
}

int filter(int input, int state, int dsec) {
  int i = 0, inc = 20; //Increment 50ms
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
void mqttmessage(int gpioout) {
    String pubString = "{\"report\":{\"light\": \"" + String(gpioO[gpioout]) + "\"}}";
    pubString.toCharArray(message_buff, pubString.length()+1);
    String topicString = "telepi/lightsensor/"+configure->getVariable("hostname")+"/"+String(gpioout);
    topicString.toCharArray(topic_buff, topicString.length()+1);
    if (mqttClient.publish(topic_buff, message_buff)==false) {
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
         digitalWrite(gpioout, HIGH);
         mqttmessage(gpioout);
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
         mqttmessage(gpioout);
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
   if (modew=="IN-R") {
     String modesw=configure->getVariable(gpiotxt+"sw");
     if (modesw=="push") {
       if (gpioP[gpioin]==LOW) {
         if (filter(gpioin, LOW, 100)) {
             changeOUT(gpioout);
             gpioP[gpioin]=HIGH;
         }
       } else {  
         if (filter(gpioin, HIGH, 300)) {
             gpioP[gpioin]=LOW;
         }
       }
     }
     if (modesw=="switch") {
       if (filter(gpioin, (gpioI[gpioin]==LOW?HIGH:LOW), 300)) {
           gpioI[gpioin]= (gpioI[gpioin]==LOW?HIGH:LOW);
           changeOUT(gpioout);
       }
     }
   }
}

void setup(void) {
  configure = new Conf();
  // configure->reset();
  tewifi = new TeWifi(configure);

  pinMode(GPIO13Led, OUTPUT);
  digitalWrite(GPIO13Led, LOW);
  blink(GPIO13Led, 300, 6);
  // Go to Config on boot
  if (filter(GPIO00Button, LOW, 700)) { //Check if button is HIGH for ~700ms
    blink(GPIO13Led, 500, 8);
    if (filter(GPIO00Button, LOW, 700)) { //Check if button is HIGH for ~700ms
      blink(GPIO13Led, 250, 16);
      WiFi.mode(WIFI_AP_STA);
      delay(500);
      WiFi.beginSmartConfig();
      while(1){
         delay(1000);
         if(WiFi.smartConfigDone()){
            Serial.println("SmartConfig Success");
            break;
         }
      }
    }
    configure->reset();
    tewifi->modeDefaultWifiAP();
  } else {
    tewifi->modeWifiClient();
  }

  pinMode(GPIO12Relay, OUTPUT);
  digitalWrite(GPIO12Relay, HIGH);

  pinMode(GPIO00Button, INPUT_PULLUP);

  WebS = new TeWebServer(80);

  // Start OTA server.
  ArduinoOTA.setHostname((const char *)tewifi->hostname.c_str());
  ArduinoOTA.begin();
  blink(GPIO13Led, 600, 3);
  mqttClient = PubSubClient(MQTT_SERVER, 1883, callback,wifiClient);
  mqttClient.connect(tewifi->hostname.c_str(),"admin","<kitipasa>");
}

void loop(void) {
 // tewifi->checkWifi();
  WebS->httpServer->handleClient();
  dealwithgpio(GPIO00Button,GPIO12Relay);
  dealwithgpio(GPIO14Pin,GPIO12Relay);
  dealwithgpio(GPIO03RX,GPIO12Relay);
  dealwithgpio(GPIO01TX,GPIO12Relay);

//  Handle OTA server.
  ArduinoOTA.handle();
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
  if (msgString.equals("{\"command\":{\"lightmode\": \"OFF\"}}")) {
    //senseMode = MODE_OFF;
  } else if (msgString.equals("{\"command\":{\"lightmode\": \"ON\"}}")) {
    //senseMode = MODE_ON;
  } else if (msgString.equals("{\"command\":{\"lightmode\": \"SENSE\"}}")) {
    //senseMode = MODE_SENSE;
  }
}



