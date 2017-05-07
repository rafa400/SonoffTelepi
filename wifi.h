#ifndef TELEPIWIFI_H
#define TELEPIWIFI_H

#include <ESP8266WiFi.h>
// #include <WiFiClient.h>
#include <DNSServer.h>

// #include <WiFiUdp.h>


// ******************************************************************************************************
// **       WIFI management        **
// **********************************
// https://github.com/sticilface/ESPmanager -- Trabajo perfecto!!!
// https://www.arduino.cc/en/Reference/WiFi

// Hostname. The setup function adds the Chip ID at the end.
#define HOSTNAME "ESP8266-OTA-"

class TeWifi {
  public:
    String hostname;
    String def_hostname;
    int modeAP;
    int apChannel;
    bool apVisible;
    DNSServer dnsServer;
    static IPAddress parseIP(String ip);
    TeWifi();
    TeWifi(Conf *conf);
    bool modeWifiAP();
    bool modeWifiClient();
    bool checkWifi();

};

#endif //TELEPIWIFI_H
