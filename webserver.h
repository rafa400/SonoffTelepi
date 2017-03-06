#ifndef TELEPIWEBSERVER_H
#define TELEPIWEBSERVER_H

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include <SPI.h>
#include <Ethernet.h>

// ******************************************************************************************************
// **       Web Server        **
// **********************************

/*  
const String sonoffsvgchar =
#include "/root/Arduino/sonoff/sonoff.svg"
  ;
  */
  /*
String mqtthtml =
#include "/root/Arduino/sonoff/mqtt.html"
  ;
*/

#define SELECTEDdef(var,option,defvar) (configure->getVariable(var,defvar)==option?"selected=\"selected\"":" ")
#define SELECTED(var,option) (configure->getVariable(var)==option?"selected=\"selected\"":" ")

#define CHECKEDdef(var,option,defvar) (configure->getVariable(var,defvar)==option?"checked=\"checked\"":" ")
#define CHECKED(var,option) (configure->getVariable(var)==option?"checked=\"checked\"":" ")

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


String VictorLozada = R"=====(body{background-size:cover;font-family:'Open Sans',sans-serif;margin:50px auto;background:red;background:-webkit-linear-gradient(left top,#16093e,#d69a54);background:-o-linear-gradient(bottom right,#16093e,#d69a54);background:-moz-linear-gradient(bottom right,#16093e,#d69a54);background:linear-gradient(to bottom right,#16093e,#d69a54)}.cform{margin:auto;width:250px;border:5px solid rgba(255,255,255,0.2);border-radius:5px}.cform .title{width:100\%;height:35px;background:#65A832;text-align:center;background:-webkit-linear-gradient(top,#65A832 0\%,#5E9C2F 85\%,#5A972C 100\%);background:-moz-linear-gradient(top,#65A832 0\%,#5E9C2F 85\%,#5A972C 100\%);background:-o-linear-gradient(top,#65A832 0\%,#5E9C2F 85\%,#5A972C 100\%);color:#FFF;font-size:20px;border-radius:3px 3px 0 0;padding-top:10px}.cform .title:after{content:'';border-top:6px solid #5A972C;border-left:6px solid transparent;border-right:6px solid transparent;display:block;position:absolute;margin:35px 15px}.cform .title span{position:absolute;display:block;text-align:center}.cform .form{background:#FFF;width:100\%;margin:auto;text-align:center;padding:10px 0}.cform .form div{text-align:justify;margin-left:34px;padding:5px 0}#gpio14,#gpio01,#gpio03,#gpio13{padding:5px;outline:none;width:50px;height:25px;border:1px solid #DEDEDE;border-radius:5px;color:#65A832;font-family:'Open Sans',sans-serif;font-size:10px;transition:linear .4s}.cform .form input[type="text"],textarea{padding:5px;outline:none;width:170px;height:20px;border:1px solid #DEDEDE;border-radius:5px;color:#65A832;font-family:'Open Sans',sans-serif;font-size:14px;transition:linear .4s}.cform .form select{padding:5px;outline:none;width:180px;height:30px;border:1px solid #DEDEDE;border-radius:5px;color:#65A832;font-family:'Open Sans',sans-serif;font-size:14px;transition:linear .4s}.cform .form select:focus{height:30px}.cform .form textarea:focus{height:70px}.cform .btn{background:#F3F3F3;text-align:center;border-radius:0 0 3px 3px;border-top:1px solid #EEE;padding:5px}.cform .btn input[type="submit"]{background:#65A832;background:linear-gradient(top,#65A832 0\%,#5E9C2F 85\%,#5A972C 100\%);padding:10px;border:none;border-radius:5px;box-shadow:0 1px 1px #54892C;color:#FFF;cursor:pointer;font-family:'Open Sans',sans-serif})=====";

String htmlhead = R"=====(<!DOCTYPE html><html><head> <title>TelePi</title> <meta name="viewport" content="width=device-width,initial-scale=1.0"> <link href="VictorLozada.css" type="text/css" rel="stylesheet"> <style> .tg {border-collapse:collapse;border-spacing:0;} .tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;} .tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;} .tg .tg-baqh{text-align:center;vertical-align:top} select{text-align:center;vertical-align:top;width:25px} option{text-align:center;vertical-align:top;width:25px} </style></head><body><form method="post">)=====";
String htmltail = R"=====(</form></body></html>)=====";

// **********************************

const String indexhtml = R"=====(<!DOCTYPE html><html><head> <title>TelePi</title> <meta name="viewport" content="width=device-width,initial-scale=1.0"/> <link href="VictorLozada.css" type="text/css" rel="stylesheet"/><script type="text/javascript"> function booting() { document.getElementById("wifisetup").onclick = function () { location.href = "wifisetup.html"; }; document.getElementById("workmode").onclick = function () { location.href = "workmode.html"; }; document.getElementById("mqtt").onclick = function () { location.href = "mqtt.html"; }; document.getElementById("update").onclick = function () { location.href = "update"; }; }</script></head><body onload="booting()"> <section class="cform"> <article class="title"> <span>Telepi ESP8266 MENU</span> </article> <article class="btn"> <input id="wifisetup" type="submit" value="Wifi Setup"> </article> <article class="btn"> <input id="workmode" type="submit" value="Work Mode"> </article> <article class="btn"> <input id="mqtt" type="submit" value="MQTT config"> </article> <article class="btn"> <input id="update" type="submit" value="Firmware Update"> </article> </section></body></html>)=====";
String wifisetuphtml = R"=====(<section class="cform"> <article class="title"> <span>Wifi Config</span> </article> <article class="form"> <div>Host Name</div> <input type="text" name="hostname" placeholder="hostame" value="%a1s" maxlength="15"> <div>Wifi Mode</div> <select id="wifimode" name="wifimode"> <option value="AP" %a2s>Access Point</option> <option value="CLI" %a3s>Client</option> <option value="ADH" %a4s>Ad Hoc</option> </select> <div>SSID</div> <input type="text" name="wifiSSID" placeholder="SSID" value="%a5s" maxlength="15"> <div>Password</div> <input type="text" name="wifipassword" placeholder="password" value="%a6s" maxlength="30"> <article class="title"> <span>LAN Config</span> </article> <select id="dhcp" name="dhcp"> <option value="DHCP" %1s>DHCP Client</option> <option value="FIXIP" %2s>Fixed IP</option> </select> <div>IP</div> <input type="text" name="Wifi_IP" placeholder="192.168.0.5" value="%3s" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$"> <div>Gateway</div> <input type="text" name="Wifi_GW" placeholder="192.168.0.1" value="%4s" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$"> <div>Netmask</div> <input type="text" name="Wifi_MSK" placeholder="255.255.255.0" value="%5s" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$"> <div>DNS1</div> <input type="text" name="Wifi_DNS" placeholder="255.255.255.0" value="%6s" required pattern="^([0-9]{1,3}\.){3}[0-9]{1,3}$"> </article> <article class="btn"> <input id="wifisetup" type="submit" name="save" value="Save"><input id="cancel" type="submit" name="cancel" value="Cancel"> </article> </section><p id="ESO">%eso</p><p>Uptime: %time</p>)=====";
String workmodehtml = R"=====( <section class="cform"> <article class="title"> <span>GPIO Config</span> </article> <article class="form"><div style="width:90%;margin-left:0px;text-align:center"> <table class="tg"> <tr> <th class="tg-baqh"></th> <th class="tg-baqh"></th> <th class="tg-baqh">Switch</th> <th class="tg-baqh">Button</th> </tr> <tr> <td class="tg-baqh">Relay</td> <td class="tg-baqh">OUT</td> <td class="tg-baqh"></td> <td class="tg-baqh"></td> </tr> <tr> <td class="tg-baqh">Led</td> <td class="tg-baqh"> <select class=rafa id="gpio13" name="gpio13"> <option value="Relay" %00a>Relay</option> <option value="Pulse" %00b>Pulse</option> <option value="NU" %00c>N/U</option> </select> </td> <td class="tg-baqh"></td> <td class="tg-baqh"></td> </tr> <tr> <td class="tg-baqh">Button</td> <td class="tg-baqh">IN-Relay<br></td> <td class="tg-baqh"><input type="radio" name="gpio00sw" value="switch" %01></td> <td class="tg-baqh"><input type="radio" name="gpio00sw" value="push" %02></td> </tr> <tr> <td class="tg-baqh">GPIO14<br></td> <td class="tg-baqh"> <select class=rafa id="gpio14" name="gpio14"> <option value="IN" %03>IN</option> <option value="IN-R" %b3>IN-Relay</option> <option value="OUT" %04>OUT</option> <option value="NU" %05>N/U</option> </select> </td> <td class="tg-baqh"><input type="radio" name="gpio14sw" value="switch" %06></td> <td class="tg-baqh"><input type="radio" name="gpio14sw" value="push" %07></td> </tr> <tr> <td class="tg-baqh">GPIO01<br></td> <td class="tg-baqh"> <select class=rafa id="gpio01" name="gpio01"> <option value="IN" %08>IN</option> <option value="IN-R" %b8>IN-Relay</option> <option value="OUT" %09>OUT</option> <option value="NU" %10>N/U</option> </select> </td> <td class="tg-baqh"><input type="radio" name="gpio01sw" value="switch" %11></td> <td class="tg-baqh"><input type="radio" name="gpio01sw" value="push" %12></td> </tr> <tr> <td class="tg-baqh">GPIO03</td> <td class="tg-baqh"> <select class=rafa id="gpio03" name="gpio03"> <option value="IN" %13>IN</option> <option value="IN-R" %b13>IN-Relay</option> <option value="OUT" %14>OUT</option> <option value="NU" %15>N/U</option> </select> </td> <td class="tg-baqh"><input type="radio" name="gpio03sw" value="switch" %16></td> <td class="tg-baqh"><input type="radio" name="gpio03sw" value="push" %17></td> </tr> </table></div> </article> <article class="btn"> <input id="wifisetup" type="submit" name="save" value="Save"><input id="cancel" type="submit" name="cancel" value="Cancel"> </article> </section>)=====";

#endif //TELEPIWEBSERVER_H

