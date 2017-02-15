#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

#include "wifi.h"

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
  co = conf;

  hostname = HOSTNAME + String(ESP.getChipId(), HEX);
  WiFi.hostname(hostname);


  dhcp = true; // (conf->getVariable("dhcp") == "false" ? false : true);
/*
  ssid = conf->getVariable("ssid");
  ssid = (ssid == "" ? "KITIPASA" : ssid);
  pass = conf->getVariable("pass");
  pass = (pass == "" ? "<kitipasa>" : pass);
*/
  ssid = "KITIPASA";
  pass = "<kitipasa>";

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
  if (!dhcp) {  //(!(dhcp= (co->getVariable("Wifi_DHCP","true")=="true"?true:false)) ) {
    
  }
  WiFi.begin(ssid.c_str(), pass.c_str());
  if (dhcp) while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
  mdns.begin("esp8266", WiFi.localIP());
  return true;
}
bool TeWifi::checkWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    int i=0;
    while ((WiFi.status() != WL_DISCONNECTED) && (i<20)) {
       delay(500); i++;
    }
    WiFi.begin(ssid.c_str(), pass.c_str());
    i=0;
    while ((WiFi.status() != WL_CONNECTED) && (i<20)) {
       delay(500); i++;
    }
  }
  return (WiFi.status() == WL_CONNECTED);
}

