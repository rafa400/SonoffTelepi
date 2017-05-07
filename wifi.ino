#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

#include "wifi.h"

TeWifi::TeWifi(void) {
  // Set Hostname.
  def_hostname = HOSTNAME + String(ESP.getChipId(), HEX);
  hostname =  configure->getVariable("hostname", def_hostname );
  configure->save();
  WiFi.hostname(hostname);
}
TeWifi::TeWifi(Conf *conf) {
  TeWifi();

  apChannel = 7;
  apVisible = true;
}
IPAddress TeWifi::parseIP(String ip) {
  int a1 = Conf::getFirstVar(ip, ".").toInt();
  int a2 = Conf::getFirstVar(ip, ".").toInt();
  int a3 = Conf::getFirstVar(ip, ".").toInt();
  int a4 = Conf::getFirstVar(ip, ".").toInt();
  return IPAddress(a1, a2, a3, a4);
}
bool TeWifi::modeWifiAP() {
  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig( TeWifi::parseIP(configure->getVariable("Wifi_IP")), TeWifi::parseIP(configure->getVariable("Wifi_GW")), TeWifi::parseIP(configure->getVariable("Wifi_MSK")) );
  WiFi.softAP("TardisTime");
  if (!WiFi.softAP(configure->getVariable("wifiSSID").c_str(), configure->getVariable("wifipassword").c_str(), apChannel, !apVisible )) {
    return false;
  }
  return true;
}
bool TeWifi::modeWifiClient() { 
  WiFi.softAPdisconnect(); // ESP's WiFi module stores its own config on chip and he expects to overwrite it clearly. Do not make him to try something common, define configs clearly and stop unrelated previous operations -- http://stackoverflow.com/questions/39688410/how-to-switch-to-normal-wifi-mode-to-access-point-mode-esp8266 
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(100);
  if (configure->getVariable("dhcp") == "FIXIP") {
  // ESP does not follow same order as arduino ( DNS is at the end) -- https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFiSTA.h#L42    
    WiFi.config(  TeWifi::parseIP(configure->getVariable("Wifi_IP")), TeWifi::parseIP(configure->getVariable("Wifi_GW")), TeWifi::parseIP(configure->getVariable("Wifi_MSK")),TeWifi::parseIP(configure->getVariable("Wifi_DNS")) );
  }
  WiFi.begin(configure->getVariable("wifiSSID").c_str(), configure->getVariable("wifipassword").c_str());
  int i=0;
  while  ((WiFi.status() != WL_CONNECTED) && (i<20)) {
    delay(500); i++;
  }
  return true;
}
bool TeWifi::checkWifi() {
  if (WiFi.status() == WL_CONNECTED) {
    // dnsServer.processNextRequest();
    // WiFi.localIP(); // 0.0.0.0
    return true;
  }
  int i=0;
  while  ((WiFi.status() != WL_CONNECTED) && (i<20)) {
    delay(500); i++;
  }
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.disconnect();
    i=0;
    while ((WiFi.status() != WL_DISCONNECTED) && (i<20)) {
       delay(500); i++;
    }
    WiFi.begin(configure->getVariable("wifiSSID").c_str(),  configure->getVariable("wifipassword").c_str());
    i=0;
    while ((WiFi.status() != WL_CONNECTED) && (i<20)) {
       delay(500); i++;
    }
  }
  return (WiFi.status() == WL_CONNECTED);
}

