#ifndef TELEPIWEBSERVER_H
#define TELEPIWEBSERVER_H

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

// ******************************************************************************************************
// **       Web Server        **
// **********************************

const char *milligramchar =
#include "/root/Arduino/sonoff/VictorLozada.css"
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

#define SELECTEDdef(var,option,defvar) (configure->getVariable(var,defvar)==option?"selected=\"selected\"":" ")
#define SELECTED(var,option) (configure->getVariable(var)==option?"selected=\"selected\"":" ")

class TeWebServer {
  public:
    TeWebServer();
    TeWebServer(int port);
    TeWebServer(int port,Conf *co);
    ESP8266WebServer *httpServer;
    ESP8266HTTPUpdateServer *httpUpdater;
    boolean authenticate();
    String jsonPage = "";
  private:
     void defineWeb();     
     Conf *co;
};


#endif //TELEPIWEBSERVER_H

