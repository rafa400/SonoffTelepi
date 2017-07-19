#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include "config.h"
#include "wifi.h"
#include "webserver.h"
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <TimeAlarms.h>
#include <ESP8266Ping.h>

#include <ESP8266HTTPClient.h>

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
//#include <CayenneMQTTESP8266.h>
char username[] = "28fa65c0-f8d5-11e6-a317-afbb545bf4f0";
char password[] = "faba8957ef391a95bb26e446a218f068bcb83e67";
char clientID[] = "4de98a90-68c0-11e7-80f0-a334be42512c";

/* //https://github.com/milesburton/Arduino-Temperature-Control-Library
 * // Tambien hay que instalar la libreria de OneWire desde el IDE de Arduino
#include <OneWire.h>
#include "DallasTemperature.h"

#define ONE_WIRE_BUS 14
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
// arrays to hold device address
DeviceAddress insideThermometer;
......
*/

/*

/**
   @brief mDNS and OTA Constants
   @{
*/
#define TelePiVersion "Ver: 3.1"
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
    yield();
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
    yield();
  }
  return true;
}

int gpioI[15]={HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
int gpioO[15]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};
int gpioP[15]={LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW};

bool changeOUT(int gpioout) {
   if (gpioO[gpioout]==LOW) {
      changeOUT_ON(gpioout);
      return false;
   } else {
      changeOUT_OFF(gpioout);
      return true;
   }
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


bool extcall(int gpioin,int gpioout,String ip) {
  if (Ping.ping(TeWifi::parseIP(ip))) {
    HTTPClient client;
    // on, off, change
    client.begin("http://"+ip+"/change");
    int httpCode = client.GET();
    if(httpCode > 0) {
        if(httpCode == HTTP_CODE_OK) {
            String payload = client.getString();
        }
    } else {
         //   client.errorToString(httpCode).c_str();
    }
    client.end();    
  }
  return true;
}
bool dealwithexternal(int gpioin,int gpioout) {
   return true;
   if (WiFi.status() == WL_CONNECTED) {
      switch (gpioin) {
        case GPIO00Button: if (configure->getVariable("ext1IP")!="") extcall(gpioin,gpioout,configure->getVariable("ext1IP")); break;
        case GPIO01TX:     if (configure->getVariable("ext2IP")!="") extcall(gpioin,gpioout,configure->getVariable("ext2IP")); break;
        case GPIO03RX:     if (configure->getVariable("ext3IP")!="") extcall(gpioin,gpioout,configure->getVariable("ext3IP")); break;
        case GPIO14Pin:    if (configure->getVariable("ext4IP")!="") extcall(gpioin,gpioout,configure->getVariable("ext4IP")); break;
        default: ;
      }
   } else
      return false;
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
             // if el otro then wget
             gpioP[gpioin]=HIGH;
             mqttmessage(gpioin,gpioP[gpioin],"in");
             dealwithexternal(gpioin,gpioout);
         }
       } else {
         if (filter(gpioin, HIGH, 100)) {
             // if el otro then wget
             gpioP[gpioin]=LOW;
             mqttmessage(gpioin,gpioP[gpioin],"in");
             dealwithexternal(gpioin,gpioout);
         }
       }
     }
     if (modesw=="switch") {
       if (filter(gpioin, (gpioI[gpioin]==LOW?HIGH:LOW), 100)) {
           gpioI[gpioin]= (gpioI[gpioin]==LOW?HIGH:LOW);
           if (modew=="IN-R") changeOUT(gpioout);
           mqttmessage(gpioin,gpioI[gpioin],"in");
           dealwithexternal(gpioin,gpioout);
       }
     }
   }
   if (modew=="OUT") {
         
   }
}

#define APDEFAULT 0
#define APSMARTCONF 1
#define APSTANDALONE 2
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
      configure->savedef();  // Make a factory reset
      blink(GPIO13Led, 250, 16);
    }
    tewifi->modeAndroidApp(); bootmode=APSMARTCONF;
  } else {
    bootmode=APDEFAULT;
    if (configure->getVariable("wifimode")=="CLI") { tewifi->modeWifiClient(); bootmode=APDEFAULT; }
    if (configure->getVariable("wifimode")=="AP")  { tewifi->modeWifiAP();     bootmode=APSTANDALONE; }
  }

  pinMode(GPIO12Relay, OUTPUT);
  digitalWrite(GPIO12Relay, HIGH);

  pinMode(GPIO00Button, INPUT_PULLUP);

  WebS = new TeWebServer(80);

  // Start OTA server.
  ArduinoOTA.setHostname((const char *)tewifi->hostname.c_str());
  ArduinoOTA.begin();
  blink(GPIO13Led, 600, 3);
  
  mqtton();

  Alarm.timerOnce(300, tewifi->checkWifi);        // called once after 5min

/*
  if (!MDNS.begin(configure->getVariable("hostname").c_str())) {
    while(1) delay(1000);
  } else
    MDNS.addService("http", "tcp", 80);
*/  

//  Cayenne.begin(username, password, clientID);

}

//unsigned long lastMillis = 0;

void loop(void) {
  WebS->httpServer->handleClient();
  if ( bootmode==APDEFAULT) {
   //tewifi->checkWifi();
   dealwithgpio(GPIO00Button,GPIO12Relay);
   dealwithgpio(GPIO14Pin,GPIO12Relay);
   dealwithgpio(GPIO03RX,GPIO12Relay);
   dealwithgpio(GPIO01TX,GPIO12Relay);
  }
  mqttcheck();
/*
  Cayenne.loop();
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    //Write data to Cayenne here. This example just sends the current uptime in milliseconds.
    Cayenne.virtualWrite(0, lastMillis);
    //Some examples of other functions you can use to send data.
    //Cayenne.celsiusWrite(1, 22.0);
    //Cayenne.luxWrite(2, 700);
    //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
  }
*/
  ArduinoOTA.handle(); //  Handle OTA server.
  yield();

}
/*
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
*/

