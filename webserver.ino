#include "webserver.h"

String timeruning(){
  int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;
    sec=sec%60;
    min=min%60;
    return String(hr)+":"+String(min)+":"+String(sec);
}

TeWebServer::TeWebServer() {
  TeWebServer(80);
}

TeWebServer::TeWebServer(int port) {
  mdns = new MDNSResponder; //ESP8266mDNS;
  mdns->begin("esp8266", WiFi.localIP());
  //co=NULL;
  jsonPage = "{ 'status':'success', 'count': 1, 'type':'Sonoff TelePi', 'time':'', 'hostname':'OpenWrt2', 'results':";
  httpServer = new ESP8266WebServer(port);
  httpUpdater = new ESP8266HTTPUpdateServer;
  mdns->addService("http", "tcp", 80); 
  defineWeb();
  httpUpdater->setup(httpServer);
  
  startAllServices();
}
TeWebServer::TeWebServer(int port,Conf *conf) {
  // co=conf;
  TeWebServer(80);
}

bool TeWebServer::startAllServices() {
  // mdns->notifyAPChange();
  //mdns->update();
  httpServer->begin();
  mdns->addService("http", "tcp", 80);  
}
bool TeWebServer::stopAllServices() {
  // mdns->notifyAPChange();
  mdns->update();
  httpServer->stop();
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
  String index2("<meta http-equiv=\"refresh\" content=\"0; url=/index.html\" />");
  WebS->httpServer->send(200, "text/html", index2 );    
}


void TeWebServer::defineWeb() {

  httpServer->on("/", []() {
    WebS->httpServer->send(200, "text/html",  WebS->jsonPage + " [ { 'Relay1':'" + tewifi->hostname + "' } ]}"  );
  });
  httpServer->on("/on", []() {
    WebS->httpServer->send(200, "text/html",  WebS->jsonPage + " [ { 'Relay1':'On' } ]}"  );
    changeOUT_ON(GPIO12Relay);
    delay(100);
  });
  httpServer->on("/off", []() {
    WebS->httpServer->send(200, "text/html",  WebS->jsonPage + " [ { 'Relay1':'Off' } ]}"  );
    changeOUT_OFF(GPIO12Relay);
    delay(100);
  });
  httpServer->on("/index.html", []() {
    String parameters[][2]={
       {"%time",timeruning()},
       {"%eso",TelePiVersion}
    };
    String index=FPSTR(indexhtml);
    for(int i=0;i<sizeof(parameters)/sizeof(parameters[0]);i++) index.replace(parameters[i][0],parameters[i][1]);
    WebS->httpServer->send(200, "text/html", index );
    delay(100);
  });
  httpServer->on("/wifisetup.html", []() {
    if ( ! configure->setArgs(*WebS->httpServer) ) {
      WebS->gotoIndexHTML();
      return;
    }
    
    String parameters[][2]={
       {"%a1s",configure->getVariable("hostname",tewifi->def_hostname)},
       {"%a2s",SELECTEDdef("wifimode","AP","CLI")},
       {"%a3s",SELECTED("wifimode","CLI")},
       {"%a4s",SELECTED("wifimode","ADH")},
       {"%a5s",configure->getVariable("wifiSSID","KITIPASA")},
       {"%a6s",configure->getVariable("wifipassword","<kitipasa>")},
       

       {"%1s",SELECTEDdef("dhcp","DHCP","DHCP")},
       {"%2s",SELECTED("dhcp","FIXIP")},
       {"%3s",configure->getVariable("Wifi_IP")},
       {"%4s",configure->getVariable("Wifi_GW")},
       {"%5s",configure->getVariable("Wifi_MSK")},
       {"%6s",configure->getVariable("Wifi_DNS")},
       {"%time",timeruning()},
       {"%eso",TelePiVersion}
    };
    String wifisetup=FPSTR(wifisetuphtml);
    for(int i=0;i<sizeof(parameters)/sizeof(parameters[0]);i++) wifisetup.replace(parameters[i][0],parameters[i][1]);
    WebS->httpServer->send(200, "text/html",wifisetup);
    delay(100);
  });
  httpServer->on("/workmode.html", []() {
    if ( ! configure->setArgs(*WebS->httpServer) ) {
      WebS->gotoIndexHTML();
      return;
    }
    CHECKEDdef("gpio00","IN","IN-R");
    String parameters[][2]={
       {"%00a",SELECTEDdef("gpio13","Relay","Relay")},
       {"%00b",SELECTED("gpio13","Pulse")},
       {"%00c",SELECTED("gpio13","NU")},
       {"%01",CHECKEDdef("gpio00sw","switch","push")},
       {"%02",CHECKED("gpio00sw","push")},
       {"%03",SELECTEDdef("gpio14","IN","NU")},
       {"%b3",SELECTED("gpio14","IN-R")},
       {"%04",SELECTED("gpio14","OUT")},
       {"%05",SELECTED("gpio14","NU")},
       {"%06",CHECKEDdef("gpio14sw","switch","switch")},
       {"%07",CHECKED("gpio14sw","push")},
       {"%08",SELECTEDdef("gpio01","IN","NU")},
       {"%b8",SELECTED("gpio01","IN-R")},       
       {"%09",SELECTED("gpio01","OUT")},
       {"%10",SELECTED("gpio01","NU")},
       {"%11",CHECKEDdef("gpio01sw","switch","switch")},
       {"%12",CHECKED("gpio01sw","push")},
       {"%13",SELECTEDdef("gpio03","IN","NU")},
       {"%b13",SELECTED("gpio03","IN-R")},              
       {"%14",SELECTED("gpio03","OUT")},
       {"%15",SELECTED("gpio03","NU")},
       {"%16",CHECKEDdef("gpio03sw","switch","switch")},
       {"%17",CHECKED("gpio03sw","push")},
       {"%time",timeruning()},
       {"%eso",TelePiVersion}
    };    
    String workmode=FPSTR(workmodehtml);
    for(int i=0;i<sizeof(parameters)/sizeof(parameters[0]);i++) workmode.replace(parameters[i][0],parameters[i][1]);
    WebS->httpServer->send(200, "text/html",workmode );
    delay(100);
  });
  httpServer->on("/mqtt.html", []() {
    if ( ! configure->setArgs(*WebS->httpServer) ) {
      WebS->gotoIndexHTML();
      return;
    }
    String parameters[][2]={
       {"%0s",CHECKEDdef("MQTTenabled","on","on")},
       {"%1s",configure->getVariable("MQTTServerPath","/TelePi/Sonoff")},
       {"%2s",configure->getVariable("MQTT_IP","192.168.0.1")},
       {"%3s",configure->getVariable("MQTT_Port","1883")},
       {"%4s",configure->getVariable("MQTTpassword","telepi")},
       {"%time",timeruning()},
       {"%eso",TelePiVersion}
    };    
    String mqttmode=FPSTR(mqtthtml);
    for(int i=0;i<sizeof(parameters)/sizeof(parameters[0]);i++) mqttmode.replace(parameters[i][0],parameters[i][1]);
    WebS->httpServer->send(200, "text/html", mqttmode );
    delay(100);
  });

  
  httpServer->on("/update.html", []() {
    String parameters[][2]={
       {"%time",timeruning()},
       {"%eso",TelePiVersion}
    };
    String updates=FPSTR(updatehtml);
    for(int i=0;i<sizeof(parameters)/sizeof(parameters[0]);i++) updates.replace(parameters[i][0],parameters[i][1]);
    WebS->httpServer->send(200, "text/html", updates );
    delay(100);
  });

  httpServer->on("/sonoff.svg", []() {
    WebS->httpServer->send(200, "image/svg+xml", FPSTR(sonoffsvgchar) );
    delay(100);
  });

  httpServer->on("/pure-release-0.6.2/pure-min.css", []() {
    WebS->httpServer->send(200, "text/css", FPSTR(purecss) );
    delay(100);
  });
  httpServer->on("/css/layouts/side-menu.css", []() {
    WebS->httpServer->send(200, "text/css", FPSTR(sidemenucss) );
    delay(100);
  });
  httpServer->on("/js/ui.js", []() {
    WebS->httpServer->send(200, "application/javascript", FPSTR(jsuijs) );
    delay(100);
  });
  
  
  httpServer->on("/config.txt", []() {
    WebS->httpServer->send(200, "text/plain", configure->readConfig() );
    delay(100);
  });
  httpServer->on("/resetconfig", []() {
    configure->savedef();
    WebS->gotoIndexHTML();
    delay(100);
    ESP.reset();
  });  
  httpServer->on("/reset", []() {
    ESP.reset();
  });  
  httpServer->on("/cero", []() {
//    free(&indexhtml);
    WebS->httpServer->send(200, "text/html", "CLEAR MADE" );
    delay(100);
  });  
  httpServer->on("/admin", []() { // http://stackoverflow.com/questions/39688410/how-to-switch-to-normal-wifi-mode-to-access-point-mode-esp8266
    if (WebS->authenticate()) { // También es utilidad para subir ficheros
      WebS->httpServer->send(200, "text/html", "HOLA");
    }
  });
  
  httpServer->onNotFound( []() {
    WebS->httpServer->send(200, "text/html", FPSTR(indexhtml));
    delay(100);
  });
}

