#ifndef TELEPIWIFI_H
#define TELEPIWIFI_H

#include <ESP8266WiFi.h>
// #include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

// #include <WiFiUdp.h>

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
    Conf *co;
};

#endif //TELEPIWIFI_H
