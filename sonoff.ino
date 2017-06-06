#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include "config.h"
#include "wifi.h"
#include "webserver.h"
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

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
#define TelePiVersion "Ver: 3.0"
/// @}

#define max_variable 150  // Max variable length 
const byte DNS_PORT = 53;

WiFiClient wifiClient;
PubSubClient mqttClient;

Conf *configure;
TeWifi *tewifi;

TeWebServer *WebS;

#define echoPin D6 // Echo Pin
#define trigPin D5 // Trigger Pin

 
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
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

  initI2C();
}

long duration, distance; // Duration used to calculate distance

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

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = duration/58.2;

// scanI2C();
testI2Cpwm();

  ArduinoOTA.handle(); //  Handle OTA server.
  yield();

}

