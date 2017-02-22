#include "webserver.h"

TeWebServer::TeWebServer() {
  TeWebServer(80);
}

TeWebServer::TeWebServer(int port) {
  //co=NULL;
  jsonPage = "{ 'status':'success', 'count': 1, 'type':'Sonoff TelePi', 'time':'', 'hostname':'OpenWrt2', 'results':";
  httpServer = new ESP8266WebServer(port);
  httpUpdater = new ESP8266HTTPUpdateServer;
  defineWeb();
  httpUpdater->setup(httpServer);
  httpServer->begin();
}
TeWebServer::TeWebServer(int port,Conf *conf) {
  // co=conf;
  TeWebServer(80);
}

boolean TeWebServer::authenticate() {
  if (httpServer->authenticate("admin", "admin")) {
    return true;
  } else {
    httpServer->requestAuthentication();
    return false; 
  }
}

void  TeWebServer::gotoIndexHTML() {
  String indexhtml("<meta http-equiv=\"refresh\" content=\"0; url=/index.html\" />");
  WebS->httpServer->send(200, "text/html", indexhtml );    
}


void TeWebServer::defineWeb() {

  httpServer->on("/", []() {
    WebS->httpServer->send(200, "text/html",  WebS->jsonPage + " [ { 'Relay1':'" + tewifi->hostname + "' } ]}"  );
  });
  httpServer->on("/on", []() {
    WebS->httpServer->send(200, "text/html",  WebS->jsonPage + " [ { 'Relay1':'On' } ]}"  );
    digitalWrite(GPIO13Led, LOW);
    digitalWrite(GPIO12Relay, HIGH);
    delay(100);
  });
  httpServer->on("/off", []() {
    WebS->httpServer->send(200, "text/html",  WebS->jsonPage + " [ { 'Relay1':'Off' } ]}"  );
    digitalWrite(GPIO13Led, HIGH);
    digitalWrite(GPIO12Relay, LOW);
    delay(100);
  });
  httpServer->on("/index.html", []() {
    WebS->httpServer->send(200, "text/html", indexhtml );
    delay(100);
  });
  httpServer->on("/wifisetup.html", []() {
    if ( ! configure->setArgs(*WebS->httpServer) ) {
      WebS->gotoIndexHTML();
      return;
    }
    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;
    String parameters[][2]={
       {"%a1s",configure->getVariable("hostname",tewifi->def_hostname)},
       {"%a2s",SELECTEDdef("wifimode","AP","CLI")},
       {"%a3s",SELECTED("wifimode","CLI")},
       {"%a4s",SELECTED("wifimode","ADH")},
       {"%a5s",configure->getVariable("wifiSSID","TELEPI")},
       {"%a6s",configure->getVariable("wifipassword","kitipasa")},
       

       {"%1s",SELECTEDdef("dhcp","DHCP","DHCP")},
       {"%2s",SELECTED("dhcp","FIXIP")},
       {"%3s",configure->getVariable("Wifi_IP","100.100.100.5")},
       {"%4s",configure->getVariable("Wifi_GW","100.100.100.1")},
       {"%5s",configure->getVariable("Wifi_MSK","255.255.255.0")},
       {"%6s",configure->getVariable("Wifi_DNS","8.8.8.8")},
       {"%time",String(hr)+":"+String(min)+":"+String(sec)}
    };
    String wifisetup=wifisetuphtml;
    for(int i=0;i<sizeof(parameters)/sizeof(parameters[0]);i++) wifisetup.replace(parameters[i][0],parameters[i][1]);
    WebS->httpServer->send(200, "text/html", wifisetup);
    delay(100);
  });
  httpServer->on("/workmode.html", []() {
    if ( ! configure->setArgs(*WebS->httpServer) ) {
      WebS->gotoIndexHTML();
      return;
    }
    String parameters[][2]={
       {"%01",CHECKEDdef("gpio00sw","switch","push")},
       {"%02",CHECKED("gpio00sw","push")},
       {"%03",SELECTEDdef("gpio14","IN","NU")},
       {"%04",SELECTED("gpio14","OUT")},
       {"%05",SELECTED("gpio14","NU")},
       {"%06",CHECKEDdef("gpio14sw","switch","switch")},
       {"%07",CHECKED("gpio14sw","push")},
       {"%08",SELECTEDdef("gpio01","IN","NU")},
       {"%09",SELECTED("gpio01","OUT")},
       {"%10",SELECTED("gpio01","NU")},
       {"%11",CHECKEDdef("gpio01sw","switch","switch")},
       {"%12",CHECKED("gpio01sw","push")},
       {"%13",SELECTEDdef("gpio03","IN","NU")},
       {"%14",SELECTED("gpio03","OUT")},
       {"%15",SELECTED("gpio03","NU")},
       {"%16",CHECKEDdef("gpio03sw","switch","switch")},
       {"%17",CHECKED("gpio03sw","push")},
    };    
    String workmode=workmodehtml;
    for(int i=0;i<sizeof(parameters)/sizeof(parameters[0]);i++) workmode.replace(parameters[i][0],parameters[i][1]);
    WebS->httpServer->send(200, "text/html", workmode );
    delay(100);
  });
  httpServer->on("/mqtt.html", []() {
   EthernetClient client;
    String mqtt="";
   if (client.connect("192.168.2.12", 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /caca.html HTTP/1.1");
    client.println("Host: 192.168.2.12");
    client.println("Connection: close");
    client.println();
    while (client.available()) {
       char mqtt=mqtt+client.read();
    }
    if (!client.connected()) client.stop();
   }
    WebS->httpServer->send(200, "text/html", mqtt );
    delay(100);
  });

/*
  httpServer->on("/sonoff.svg", []() {
    WebS->httpServer->send(200, "image/svg+xml", sonoffsvgchar );
    delay(100);
  });
*/

  httpServer->on("/VictorLozada.css", []() {
    WebS->httpServer->send(200, "text/css", VictorLozada );
    delay(100);
  });
  httpServer->on("/config.txt", []() {
    WebS->httpServer->send(200, "text/plain", configure->readConfig() );
    delay(100);
  });
  httpServer->on("/resetconfig", []() {
    configure->reset();
    WebS->gotoIndexHTML();
    delay(100);
    ESP.reset();
  });  
  httpServer->on("/admin", []() { // http://stackoverflow.com/questions/39688410/how-to-switch-to-normal-wifi-mode-to-access-point-mode-esp8266
    if (WebS->authenticate()) { // También es utilidad para subir ficheros
      WebS->httpServer->send(200, "text/html", "HOLA");
    }
  });
  
  httpServer->onNotFound( []() {
    WebS->httpServer->send(200, "text/html", indexhtml );
    delay(100);
  });
}
