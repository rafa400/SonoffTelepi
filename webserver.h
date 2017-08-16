#ifndef TELEPIWEBSERVER_H
#define TELEPIWEBSERVER_H

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include <SPI.h>
#include <Ethernet.h>

#include "html.h"

// ******************************************************************************************************
// **       Web Server        **
// **********************************

#define SELECTEDdef(var,option,defvar) (configure->getVariable(var,defvar)==option?"selected=\"selected\"":" ")
#define SELECTED(var,option) (configure->getVariable(var)==option?"selected=\"selected\"":" ")

#define CHECKEDdef(var,option,defvar) (configure->getVariable(var,defvar)==option?"checked=\"checked\"":" ")
#define CHECKED(var,option) (configure->getVariable(var)==option?"checked=\"checked\"":" ")

#define CHECKdef(var,option,defvar) (configure->getVariable(var,defvar)==option?"checked":" ")
#define CHECK(var,option) (configure->getVariable(var)==option?"checked":" ")

class TeWebServer {
  public:
    TeWebServer();
    TeWebServer(int port);
    TeWebServer(int port,Conf *co);
    bool startAllServices();
    bool stopAllServices();
    MDNSResponder *mdns;
    ESP8266WebServer *httpServer;
    ESP8266HTTPUpdateServer *httpUpdater;
    boolean authenticate();
    String jsonPage = "";
  private:
     void defineWeb();   
     void gotoIndexHTML();
     Conf *co;
};

#endif //TELEPIWEBSERVER_H

