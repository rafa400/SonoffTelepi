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
    String indexhtml(indexhtmlchar);
    WebS->httpServer->send(200, "text/html", indexhtml );
    delay(100);
  });
  httpServer->on("/workmode.html", []() {
    String workmodehtml(workmodehtmlchar);
    WebS->httpServer->send(200, "text/html", workmodehtml );
    delay(100);
  });

  httpServer->on("/wifisetup.html", []() {
    String content = " ";  // Meter un espacio en blanco en sprintf cuelga!!

    if (WebS->httpServer->args() > 0 ) {
      for ( uint8_t i = 0; i < WebS->httpServer->args(); i++ ) {
          content = content + "\r\n" + WebS->httpServer->argName(i) + "--" + WebS->httpServer->arg(i);
          configure->setVariable( WebS->httpServer->argName(i),WebS->httpServer->arg(i));
      }
      configure->setUserPassword("admin","admin");
      configure->save();
    }

    String wifisetuphtml(wifisetuphtmlchar);

  /*
    int sec = millis() / 1000;
    int min = sec / 60;
    int hr = min / 60;
    content.c_str(), hr, min % 60, sec % 60);
  */
    wifisetuphtml.replace("%a1s",configure->getVariable("hostname",tewifi->def_hostname));
    wifisetuphtml.replace("%a2s",SELECTEDdef("wifimode","AP","CLI"));
    wifisetuphtml.replace("%a3s",SELECTED("wifimode","CLI"));
    wifisetuphtml.replace("%a4s",SELECTED("wifimode","ADH"));    
  
    wifisetuphtml.replace("%1s",SELECTEDdef("dhcp","DHCP","DHCP"));
    wifisetuphtml.replace("%2s",SELECTED("dhcp","FIXIP"));
    wifisetuphtml.replace("%3s",configure->getVariable("Wifi_IP","100.100.100.5"));
    wifisetuphtml.replace("%4s",configure->getVariable("Wifi_GW","100.100.100.1"));
    wifisetuphtml.replace("%5s",configure->getVariable("Wifi_MSK","255.255.255.0"));
    wifisetuphtml.replace("%6s",configure->getVariable("Wifi_DNS","8.8.8.8"));
    wifisetuphtml.replace("Uptime",content);

    WebS->httpServer->send(200, "text/html", (wifisetuphtml).c_str());
    delay(100);
  });

  httpServer->on("/VictorLozada.css", []() {
    String milligram(milligramchar);
    WebS->httpServer->send(200, "text/css", milligram );
    delay(100);
  });
  
  httpServer->on("/gradient.svg", []() {
    String gradient(gradientsvgchar);
    WebS->httpServer->send(200, "image/svg+xml", gradient );
    delay(100);
  });

  httpServer->on("/config.txt", []() {
    WebS->httpServer->send(200, "text/plain", configure->readConfig() );
    delay(100);
  });
  httpServer->on("/admin", []() { // http://stackoverflow.com/questions/39688410/how-to-switch-to-normal-wifi-mode-to-access-point-mode-esp8266
    if (WebS->authenticate()) { // También es utilidad para subir ficheros
      WebS->httpServer->send(200, "text/html", "HOLA");
    }
  });
  
  httpServer->onNotFound( []() {
    String indexhtml(indexhtmlchar);
    WebS->httpServer->send(200, "text/html", indexhtml );
    configure->reset();
    delay(100);
  });
}
