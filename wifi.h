#include <FileIO.h>
#include <Console.h>
#include <BridgeSSLClient.h>
#include <BridgeUdp.h>
#include <Mailbox.h>
#include <Process.h>
#include <YunClient.h>
#include <HttpClient.h>
#include <BridgeClient.h>
#include <YunServer.h>
#include <Bridge.h>
#include <BridgeServer.h>

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

// Hostname. The setup function adds the Chip ID at the end.
#define HOSTNAME "ESP8266-OTA-"
  

class TeWifi {
  public:
    String hostname;
    String def_hostname;
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
    bool checkWifi();
  private:
    Conf *co;
};

#endif //TELEPIWIFI_H
