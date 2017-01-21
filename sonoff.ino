#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include <WiFiUdp.h>
#include <FS.h>
#include <ArduinoOTA.h>

/**
 * @brief mDNS and OTA Constants
 * @{
 */
#define HOSTNAME "ESP8266-OTA-" ///< Hostename. The setup function adds the Chip ID at the end.
/// @}

String getFirstVar(String *text,String separator) {
     int8_t pos = text->indexOf(separator);  
     if (pos == -1) return (*text);
     String first = text->substring(0, pos);
     *text = text->substring(pos + 1);
     text->trim();
     first.trim();
     return first;
}


// ******************************************************************************************************
// **       WIFI management        **
// **********************************
// https://github.com/sticilface/ESPmanager -- Trabajo perfecto!!!
// https://www.arduino.cc/en/Reference/WiFi

class SettingsWifi {
  public:
    int modeAP;
    char* ssid;
    char* pass;
    String ip;
    String mask;
    String gatew;
    int channel;
    bool visible;
    static IPAddress parseIP(String ip);
    SettingsWifi();
};
SettingsWifi::SettingsWifi(void) {
    ssid = "KITIPASA";
    pass = "petard@s2016";
}
IPAddress SettingsWifi::parseIP(String ip) {
  int a1=getFirstVar(&ip,",").toInt();
  int a2=getFirstVar(&ip,",").toInt();
  int a3=getFirstVar(&ip,",").toInt();
  int a4=getFirstVar(&ip,",").toInt();
  return IPAddress(a1,a2,a3,a4);
}

SettingsWifi settings;

bool modeWifiAP(String apIP,String apGTW, String apMSK) {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig( SettingsWifi::parseIP(apIP),SettingsWifi::parseIP(apGTW),SettingsWifi::parseIP(apMSK) );
  WiFi.softAP("TardisTime"); 

  if (!WiFi.softAP(settings.ssid, settings.pass, settings.channel, !settings.visible )) {
    return false;
  }
    
  return true;
}
bool modeWifiClient(String apIP,String apGTW, String apMSK) {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig( SettingsWifi::parseIP(apIP),SettingsWifi::parseIP(apGTW),SettingsWifi::parseIP(apMSK) );
  WiFi.softAP("TardisTime"); 
    
//    WiFi.hostname(hostname);
//  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
    
  return true;
}

// ******************************************************************************************************
// **       Web Server        **
// **********************************


MDNSResponder mdns;

char* ssid = "KITIPASA";
char* password = "petard@s2016";

const char *milligramchar = 
#include "/root/Arduino/sonoff/milligram.min.css"
;
const char *indexhtmlchar = 
#include "/root/Arduino/sonoff/index.html"
;
const char *workmodehtmlchar = 
#include "/root/Arduino/sonoff/workmode.html"
;
const char *wifisetuphtmlchar = 
#include "/root/Arduino/sonoff/wifisetup.html"
;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

String jsonPage = "";
// String milligram ="";

boolean authenticate(ESP8266WebServer server) {
  if(server.authenticate("admin","admin")){ 
       return true;
    } else {
       server.requestAuthentication();
       return false;
    }
}

// ******************************************************************************************************
// **       PROGRAM        **
// **********************************

const int GPIO00Button = 0;
const int GPIO12Relay = 12;
const int GPIO13Led = 13;

int buttonState=HIGH;
int buttonStateOld=HIGH;

void blink(int gpionum,int one,int num) {
  int state=digitalRead(gpionum);
  for (int i=0; i<num;i++) {
    digitalWrite(gpionum, LOW);
    delay(one/2);  
    digitalWrite(gpionum, HIGH);
    delay(one/2);
  }
  digitalWrite(gpionum, state);
  return;
}

int filter(int input,int state,int dsec) {
  int i=0,inc=25; //Increment 50ms
  while (i<dsec) {
     delay(inc);
     i+=inc;
     pinMode(GPIO00Button,INPUT);
     if (digitalRead(input)!=state) return false;
  }
  return true;
}

bool loadConfig(String *ssid, String *pass) {
  File configFile = SPIFFS.open("/config.txt", "r");
  if (!configFile) return false;
  String content = configFile.readString();
  configFile.close();
  content.trim();
  content.replace("\r","\n");
  content.replace("\n\n","\n");

  *ssid = getFirstVar(&content,"\n");
  *pass = getFirstVar(&content,"\n");
  return true;
} 

bool saveConfig(String *ssid, String *pass) {
  File configFile = SPIFFS.open("/config.txt", "w");
  if (!configFile) return false;
  configFile.println(*ssid);
  configFile.println(*pass);
  configFile.close();
  return true;
}

void setup(void){
  jsonPage = "{ 'status':'success', 'count': 1, 'type':'Sonoff TelePi', 'time':'', 'hostname':'OpenWrt2', 'results':";
  // Set Hostname.
  String hostname(HOSTNAME);
  hostname += String(ESP.getChipId(), HEX);
  WiFi.hostname(hostname);

  pinMode(GPIO13Led, OUTPUT);
  digitalWrite(GPIO13Led, LOW);
  blink(GPIO13Led,600,3);
   if (filter(GPIO00Button,LOW,700)) {  //Check if button is HIGH for ~700ms
     blink(GPIO13Led,500,8);
   }

  pinMode(GPIO12Relay, OUTPUT);
  digitalWrite(GPIO12Relay, HIGH);

  pinMode(GPIO00Button,INPUT);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  mdns.begin("esp8266", WiFi.localIP());
  
  httpServer.on("/",[](){
    String hostname(HOSTNAME);
    hostname += String(ESP.getChipId(), HEX);
    WiFi.hostname(hostname);
    httpServer.send(200, "text/html", jsonPage + " [ { 'Relay1':'"+hostname+"' } ]}"  );
  });
  httpServer.on("/on",[](){
    httpServer.send(200, "text/html", jsonPage + " [ { 'Relay1':'On' } ]}"  );
    digitalWrite(GPIO13Led, LOW);
    digitalWrite(GPIO12Relay, HIGH);
    delay(100);
  });
  httpServer.on("/off",[](){
    httpServer.send(200, "text/html", jsonPage + " [ { 'Relay1':'Off' } ]}"  );
    digitalWrite(GPIO13Led, HIGH);
    digitalWrite(GPIO12Relay, LOW);
    delay(100); 
  });
  httpServer.on("/index.html",[](){
    String indexhtml(indexhtmlchar);
    httpServer.send(200, "text/html", indexhtml );
    delay(100); 
  });  
  httpServer.on("/workmode.html",[](){
    String workmodehtml(workmodehtmlchar);
    httpServer.send(200, "text/html", workmodehtml );
    delay(100); 
  });  
  httpServer.on("/wifisetup.html",[](){
    String content = "";
    if (httpServer.args() > 0 ) {
      for ( uint8_t i = 0; i < httpServer.args(); i++ ) {
        //if (httpServer.argName(i) == "fname")
        {
         content = content + "\r\n"+ httpServer.argName(i) + "--" + httpServer.arg(i);
        }
      }
    }
    char charBuf[150];
    content.toCharArray(charBuf, 150);
    
    String wifisetuphtml(wifisetuphtmlchar);
    char buffer[wifisetuphtml.length()+100];
    String final;
    
    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;
    
    sprintf(buffer,wifisetuphtmlchar,"checked","","100.100.100.5","255.255.255.0","100.100.100.1","8.8.8.8",charBuf, hr, min % 60, sec % 60);
    httpServer.send(200, "text/html", buffer );
    delay(100); 
  });  

  httpServer.on("/milligram.min.css",[](){
    String milligram(milligramchar);
    httpServer.send(200, "text/css", milligram );
    delay(100); 
  });  
  httpServer.on("/config.txt",[](){
    File configFile = SPIFFS.open("/config.txt", "r");
    String content = "EMPTY!";
    if (configFile) content = configFile.readString();
    configFile.close();
    httpServer.send(200, "text/css", content );
    delay(100); 
  });  
  httpServer.on("/admin", [](){ // http://stackoverflow.com/questions/39688410/how-to-switch-to-normal-wifi-mode-to-access-point-mode-esp8266
    if(httpServer.authenticate("admin","admin")){  // También es utilidad para subir ficheros
      //createAccessPoint();
      httpServer.sendHeader("Connection", "close");
      httpServer.sendHeader("Access-Control-Allow-Origin", "*");
      httpServer.send(200, "text/html", "HOLA");
    }
    else{
       return httpServer.requestAuthentication();
    }
  });
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  mdns.addService("http", "tcp", 80);
   // Start OTA server.
  ArduinoOTA.setHostname((const char *)hostname.c_str());
  ArduinoOTA.begin();
  blink(GPIO13Led,600,3);    
}

void loop(void){
  httpServer.handleClient();
  buttonStateOld=buttonState;
  buttonState=digitalRead(GPIO00Button);
  if ( (buttonState!=buttonStateOld) && (buttonStateOld==HIGH) ) {
    pinMode(GPIO00Button,INPUT);
    if (digitalRead(GPIO00Button)==LOW) {
       if (filter(GPIO00Button,LOW,300)) {  //Check if button is HIGH for ~300ms
          if (digitalRead(GPIO12Relay)==HIGH) {
            digitalWrite(GPIO12Relay, LOW);
            digitalWrite(GPIO13Led, HIGH);
          } else {
            digitalWrite(GPIO12Relay, HIGH);
            digitalWrite(GPIO13Led, LOW);
          }   
       }
    }
  }
  // Handle OTA server.
  ArduinoOTA.handle();
  yield();
} 


