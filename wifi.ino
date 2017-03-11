#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

#include "wifi.h"

TeWifi::TeWifi(void) {
  configure->getVariable("wifiSSID","KITIPASA");
  configure->getVariable("wifipassword","<kitipasa>");
  configure->getVariable("Wifi_IP","192.168.0.20");
  configure->getVariable("Wifi_GW","192.168.0.1");
  configure->getVariable("Wifi_MSK","255.255.255.0");
  configure->getVariable("Wifi_DNS","8.8.8.8");
  
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
  int a1 = Conf::getFirstVar(&ip, ",").toInt();
  int a2 = Conf::getFirstVar(&ip, ",").toInt();
  int a3 = Conf::getFirstVar(&ip, ",").toInt();
  int a4 = Conf::getFirstVar(&ip, ",").toInt();
  return IPAddress(a1, a2, a3, a4);
}
bool TeWifi::modeWifiAP() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig( TeWifi::parseIP(configure->getVariable("Wifi_IP")), TeWifi::parseIP(configure->getVariable("Wifi_GW")), TeWifi::parseIP(configure->getVariable("Wifi_MSK")) );
  WiFi.softAP("TardisTime");
  if (!WiFi.softAP(configure->getVariable("wifiSSID").c_str(), configure->getVariable("wifipassword").c_str(), apChannel, !apVisible )) {
    return false;
  }
  return true;
}
bool TeWifi::modeDefaultWifiAP() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig( TeWifi::parseIP("192.168.0.1"), TeWifi::parseIP("192.168.0.1"), TeWifi::parseIP("255.255.255.0") );
  WiFi.softAP("-TelePi-Sonoff-", "kitipasa" );
  if (!WiFi.softAP("-TelePi-Sonoff-", "kitipasa" )) {
    return false;
  }
  dnsServer.start(DNS_PORT, "*", TeWifi::parseIP("192.168.0.1"));
  return true;
}
bool TeWifi::modeWifiClient() {
  WiFi.begin(configure->getVariable("wifiSSID").c_str(), configure->getVariable("wifipassword").c_str());
  if (configure->getVariable("dhcp") == "FIXIP") {
    WiFi.config(  TeWifi::parseIP(configure->getVariable("Wifi_IP")),TeWifi::parseIP(configure->getVariable("Wifi_DNS")), TeWifi::parseIP(configure->getVariable("Wifi_GW")), TeWifi::parseIP(configure->getVariable("Wifi_MSK")) );
  }
  int i=0;
  while  ((WiFi.status() != WL_CONNECTED) && (i<20)) {
    delay(500); i++;
  }
  if (configure->getVariable("dhcp") == "FIXIP") {
    WiFi.config(  TeWifi::parseIP(configure->getVariable("Wifi_IP")),TeWifi::parseIP(configure->getVariable("Wifi_DNS")), TeWifi::parseIP(configure->getVariable("Wifi_GW")), TeWifi::parseIP(configure->getVariable("Wifi_MSK")) );
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

