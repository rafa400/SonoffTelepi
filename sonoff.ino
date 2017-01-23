#include <ESP8266WiFi.h>
// #include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

// #include <WiFiUdp.h>
#include <FS.h>
#include <ArduinoOTA.h>

/**
   @brief mDNS and OTA Constants
   @{
*/
#define HOSTNAME "ESP8266-OTA-" ///< Hostename. The setup function adds the Chip ID at the end.
/// @}

#define max_variable 150  // Max variable length 
const byte DNS_PORT = 53;

// ******************************************************************************************************
// **       Config management        **
// ************************************
class Conf {
  public:
    Conf();
    bool load();
    bool save();
    String getConfig();
    void setConfig(String vars);
    void addConfig(String varname, String varval);
    static String getFirstVar(String *text, String separator);
    String getVariable(String varname);
    char* getVariableChar(String varname);
  private:
    String variables;
    const String equal="=>";
};
Conf::Conf() {
  variables = "";
  load();
}
bool Conf::load() {
  File configFile = SPIFFS.open("/config.txt", "r");
  if (!configFile) return false;
  variables = configFile.readString();
  configFile.close();
  variables.trim();
  variables.replace("\r", "\n");
  variables.replace("\n\n", "\n");
  return true;
}
bool Conf::save() {
  File configFile = SPIFFS.open("/config.txt", "w");
  if (!configFile) return false;
  configFile.print(variables);
  configFile.close();
  return true;
}
String Conf::getConfig() {
  return variables;
}
void Conf::setConfig(String vars) {
  variables = vars;
}
void Conf::addConfig(String varname, String varval) {
  variables = variables + varname + "=>" + varval + "\r\n";
}
String Conf::getFirstVar(String *text, String separator) {
  int8_t pos = text->indexOf(separator);
  if (pos == -1) return (*text);
  String first = text->substring(0, pos);
  *text = text->substring(pos + 1);
  text->trim();
  first.trim();
  return first;
}
String Conf::getVariable(String varname) {
  int8_t pos = variables.indexOf(varname+equal);
  if (pos == -1) return ("");
  String first = variables.substring(pos + varname.length() + equal.length());
  pos = first.indexOf("\n");
  first = first.substring(0, pos);
  first.trim();
  return first;
}
char* Conf::getVariableChar(String varname) {
  return (char *)varname.c_str();
}

// ******************************************************************************************************
// **       WIFI management        **
// **********************************
// https://github.com/sticilface/ESPmanager -- Trabajo perfecto!!!
// https://www.arduino.cc/en/Reference/WiFi

class TeWifi {
  public:
    String hostname;
    int modeAP;
    String ssid;
    String pass;
    bool dhcp;
    String apIP;
    String apGTW;
    String apMSK;
    int apChannel;
    bool apVisible;
    MDNSResponder mdns;
    DNSServer dnsServer;
    static IPAddress parseIP(String ip);
    TeWifi();
    TeWifi(Conf *conf);
    bool modeWifiAP();
    bool modeDefaultWifiAP();
    bool modeWifiClient();
  private:
    Conf *_conf;  
};
TeWifi::TeWifi(void) {
  dhcp = true;
  ssid = "KITIPASA";
  pass = "<kitipasa>";
  // Set Hostname.
  hostname = HOSTNAME + String(ESP.getChipId(), HEX);
  WiFi.hostname(hostname);
}
TeWifi::TeWifi(Conf *conf) {
  TeWifi();
  _conf = conf;

  hostname = HOSTNAME + String(ESP.getChipId(), HEX);
  WiFi.hostname(hostname);
  
  dhcp = (conf->getVariable("dhcp")=="false"?false:true);
  ssid = conf->getVariable("ssid");
  ssid = (ssid==""?"KITIPASA":ssid);
  pass = conf->getVariable("pass");
  pass = (pass==""?"<kitipasa>":pass);

  apIP = '192.168.0.1';
  apGTW = '192.168.0.1';
  apMSK = '255.255.255.0';
  apChannel = 7;
  apVisible = true;
}
IPAddress TeWifi::parseIP(String ip) {
  int a1 = Conf::getFirstVar(&ip, ",").toInt();
  int a2 = Conf::getFirstVar(&ip, ",").toInt();
  int a3 = Conf::getFirstVar(&ip, ",").toInt();
  int a4 = Conf::getFirstVar(&ip, ",").toInt();
  return IPAddress(a1, a2, a3, a4);
}
bool TeWifi::modeWifiAP() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig( TeWifi::parseIP(apIP), TeWifi::parseIP(apGTW), TeWifi::parseIP(apMSK) );
  WiFi.softAP("TardisTime");
  if (!WiFi.softAP(ssid.c_str(), pass.c_str(), apChannel, !apVisible )) {
    return false;
  }
  return true;
}
bool TeWifi::modeDefaultWifiAP() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig( TeWifi::parseIP("192.168.0.1"), TeWifi::parseIP("192.168.0.1"), TeWifi::parseIP("255.255.255.0") );
  WiFi.softAP("-TelePi-Sonoff-", "kitipasa" );
  if (!WiFi.softAP("-TelePi-Sonoff-", "kitipasa" )) {
    return false;
  }
  dnsServer.start(DNS_PORT, "*", TeWifi::parseIP("192.168.0.1"));
  return true;
}
bool TeWifi::modeWifiClient() {
  if (!dhcp) {
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig( TeWifi::parseIP(apIP), TeWifi::parseIP(apGTW), TeWifi::parseIP(apMSK) );
    WiFi.softAP("TardisTime");
    //    WiFi.hostname(hostname);
  } 
  WiFi.begin(ssid.c_str(), pass.c_str());
  if (dhcp) while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  mdns.begin("esp8266", WiFi.localIP());
  return true;
}

// ******************************************************************************************************
// **       Web Server        **
// **********************************

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
const char *gradientsvgchar =
#include "/root/Arduino/sonoff/gradient.svg"
  ;


  
String jsonPage = "";
// String milligram ="";

boolean authenticate(ESP8266WebServer *server) {
  if (server->authenticate("admin", "admin")) {
    return true;
  } else {
    server->requestAuthentication();
    return false;
  }
}

// ******************************************************************************************************
// **       PROGRAM        **
// **********************************

const int GPIO00Button = 0;
const int GPIO12Relay = 12;
const int GPIO13Led = 13;

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
  int i = 0, inc = 25; //Increment 50ms
  while (i < dsec) {
    delay(inc);
    i += inc;
    pinMode(GPIO00Button, INPUT);
    if (digitalRead(input) != state) return false;
  }
  return true;
}

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

Conf *configuration;
TeWifi *tewifi;

void setup(void) {
  configuration = new Conf();
  tewifi = new TeWifi(configuration);

  jsonPage = "{ 'status':'success', 'count': 1, 'type':'Sonoff TelePi', 'time':'', 'hostname':'OpenWrt2', 'results':";

  pinMode(GPIO13Led, OUTPUT);
  digitalWrite(GPIO13Led, LOW);
  blink(GPIO13Led, 600, 3);
  if (filter(GPIO00Button, LOW, 700)) { //Check if button is HIGH for ~700ms
    blink(GPIO13Led, 500, 8);
    tewifi->modeWifiAP();
  } else {
    tewifi->modeWifiClient();    
  }

  pinMode(GPIO12Relay, OUTPUT);
  digitalWrite(GPIO12Relay, HIGH);

  pinMode(GPIO00Button, INPUT);

  httpServer.on("/", []() {
    httpServer.send(200, "text/html", jsonPage + " [ { 'Relay1':'" + tewifi->hostname + "' } ]}"  );
  });
  httpServer.on("/on", []() {
    httpServer.send(200, "text/html", jsonPage + " [ { 'Relay1':'On' } ]}"  );
    digitalWrite(GPIO13Led, LOW);
    digitalWrite(GPIO12Relay, HIGH);
    delay(100);
  });
  httpServer.on("/off", []() {
    httpServer.send(200, "text/html", jsonPage + " [ { 'Relay1':'Off' } ]}"  );
    digitalWrite(GPIO13Led, HIGH);
    digitalWrite(GPIO12Relay, LOW);
    delay(100);
  });
  httpServer.on("/index.html", []() {
    String indexhtml(indexhtmlchar);
    httpServer.send(200, "text/html", indexhtml );
    delay(100);
  });
  httpServer.on("/workmode.html", []() {
    String workmodehtml(workmodehtmlchar);
    httpServer.send(200, "text/html", workmodehtml );
    delay(100);
  });
  httpServer.on("/wifisetup.html", []() {
    String content = "";
    if (httpServer.args() > 0 ) {
      for ( uint8_t i = 0; i < httpServer.args(); i++ ) {
        //if (httpServer.argName(i) == "fname")
        {
          content = content + "\r\n" + httpServer.argName(i) + "--" + httpServer.arg(i);
        }
      }
    }

    String wifisetuphtml(wifisetuphtmlchar);
    char buffer[wifisetuphtml.length() + 1000];

    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;

    sprintf(buffer, wifisetuphtmlchar, "selected=\"selected\"", "", "100.100.100.5", "100.100.100.1", "255.255.255.0", "8.8.8.8", content.c_str(), hr, min % 60, sec % 60);
    httpServer.send(200, "text/html", buffer );
    delay(100);
  });

  httpServer.on("/milligram.min.css", []() {
    String milligram(milligramchar);
    httpServer.send(200, "text/css", milligram );
    delay(100);
  });
  httpServer.on("/gradient.svg", []() {
    String gradient(gradientsvgchar);
    httpServer.send(200, "image/svg+xml", gradient );
    delay(100);
  });
  
  httpServer.on("/config.txt", []() {
    File configFile = SPIFFS.open("/config.txt", "r");
    String content = "EMPTY!";
    if (configFile) content = configFile.readString();
    configFile.close();
    httpServer.send(200, "text/css", content );
    delay(100);
  });
  httpServer.on("/admin", []() { // http://stackoverflow.com/questions/39688410/how-to-switch-to-normal-wifi-mode-to-access-point-mode-esp8266
    if (authenticate(&httpServer)) { // También es utilidad para subir ficheros
      httpServer.send(200, "text/html", "HOLA");
    }
  });
  httpServer.onNotFound( []() {
    String indexhtml(indexhtmlchar);
    httpServer.send(200, "text/html", indexhtml );
    delay(100);
  });


  httpUpdater.setup(&httpServer);
  httpServer.begin();
  tewifi->mdns.addService("http", "tcp", 80);
  // Start OTA server.
  ArduinoOTA.setHostname((const char *)tewifi->hostname.c_str());
  ArduinoOTA.begin();
  blink(GPIO13Led, 600, 3);
}

void loop(void) {
  tewifi->dnsServer.processNextRequest();
  httpServer.handleClient();
  buttonStateOld = buttonState;
  buttonState = digitalRead(GPIO00Button);
  if ( (buttonState != buttonStateOld) && (buttonStateOld == HIGH) ) {
    pinMode(GPIO00Button, INPUT);
    if (digitalRead(GPIO00Button) == LOW) {
      if (filter(GPIO00Button, LOW, 300)) { //Check if button is HIGH for ~300ms
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
  // Handle OTA server.
  ArduinoOTA.handle();
  yield();
}



