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

WiFiClient wifiClient;
PubSubClient mqttClient;

Conf *configure;
TeWifi *tewifi;

TeWebServer *WebS;

void setup(void) {
  configure = new Conf();
  tewifi = new TeWifi(configure);

  pinMode(GPIO13Led, OUTPUT);
  digitalWrite(GPIO13Led, LOW);
  blink(GPIO13Led, 300, 6);
  // Go to Config on boot
  if (filter(GPIO00Button, LOW, 700)) { //Check if button is HIGH for ~700ms
    blink(GPIO13Led, 500, 8);
    if (filter(GPIO00Button, LOW, 700)) { //Check if button is HIGH for ~700ms
      blink(GPIO13Led, 250, 16);
      WiFi.beginSmartConfig();
      while(1){
         delay(1000);
         if(WiFi.smartConfigDone()){
            Serial.println("SmartConfig Success");
            break;
         }
      }
    }
    tewifi->modeWifiAP();
  } else {
    tewifi->modeWifiClient();
  }

  pinMode(GPIO12Relay, OUTPUT);
  digitalWrite(GPIO12Relay, HIGH);

  mqttClient = PubSubClient(MQTT_SERVER, 1883, callback,wifiClient);
  mqttClient.connect(tewifi->hostname.c_str(),"admin","<kitipasa>");
  pinMode(GPIO00Button, INPUT_PULLUP);

  WebS = new TeWebServer(80);

  tewifi->mdns.addService("http", "tcp", 80);
  // Start OTA server.
  ArduinoOTA.setHostname((const char *)tewifi->hostname.c_str());
  ArduinoOTA.begin();
  blink(GPIO13Led, 600, 3);
}

int seconds = millis() / 1000;
char message_buff[100];

void loop(void) {
  tewifi->checkWifi();
  tewifi->dnsServer.processNextRequest();
  WebS->httpServer->handleClient();
  buttonStateOld = buttonState;
  pinMode(GPIO00Button, INPUT_PULLUP);
  buttonState = digitalRead(GPIO00Button);
  if ( (buttonState != buttonStateOld) && (buttonStateOld == HIGH) ) {
    pinMode(GPIO00Button, INPUT_PULLUP);
    if (digitalRead(GPIO00Button) == LOW) {
      if (filter(GPIO00Button, LOW, 50)) { //Check if button is HIGH for ~300ms
        if (digitalRead(GPIO12Relay) == HIGH) {
          digitalWrite(GPIO12Relay, LOW);
          digitalWrite(GPIO13Led, HIGH);
        } else {
          digitalWrite(GPIO12Relay, HIGH);
          digitalWrite(GPIO13Led, LOW);
        }
      }
    }
  }
//  Handle OTA server.
  ArduinoOTA.handle();
  yield();
  int sec2=millis()/1000;
  if (sec2>seconds+10) {
    String pubString = "{\"report\":{\"light\": \"" + String(0) + "\"}}";
    pubString.toCharArray(message_buff, pubString.length()+1);
    mqttClient.publish("arduino/lightsensor", message_buff);
    seconds=sec2;
  } 
  pinMode(GPIO03RX, INPUT_PULLUP);
  if (filter(GPIO03RX, LOW, 150)) {
    blink(GPIO13Led, 600, 3);
  }
  pinMode(GPIO01TX, INPUT_PULLUP);
  if (filter(GPIO01TX, LOW, 150)) {
    blink(GPIO13Led, 600, 3);
  }
  pinMode(GPIO14Pin, INPUT_PULLUP);
  if (filter(GPIO14Pin, LOW, 150)) {
    blink(GPIO13Led, 600, 3);
  }
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



