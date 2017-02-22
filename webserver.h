#ifndef TELEPIWEBSERVER_H
#define TELEPIWEBSERVER_H

#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#include <SPI.h>
#include <Ethernet.h>

// ******************************************************************************************************
// **       Web Server        **
// **********************************

String indexhtml =
#include "/root/Arduino/sonoff/index.html"
  ;
String wifisetuphtml =
#include "/root/Arduino/sonoff/wifisetup.html"
  ;
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
    ESP8266WebServer *httpServer;
    ESP8266HTTPUpdateServer *httpUpdater;
    boolean authenticate();
    String jsonPage = "";
  private:
     void defineWeb();   
     void gotoIndexHTML();
     Conf *co;
};


String VictorLozada = R"=====(body{background-size:cover;font-family:'Open Sans',sans-serif;margin:50px auto;background:red;background:-webkit-linear-gradient(left top,#16093e,#d69a54);background:-o-linear-gradient(bottom right,#16093e,#d69a54);background:-moz-linear-gradient(bottom right,#16093e,#d69a54);background:linear-gradient(to bottom right,#16093e,#d69a54)}.cform{margin:auto;width:250px;border:5px solid rgba(255,255,255,0.2);border-radius:5px}.cform .title{width:100\%;height:35px;background:#65A832;text-align:center;background:-webkit-linear-gradient(top,#65A832 0\%,#5E9C2F 85\%,#5A972C 100\%);background:-moz-linear-gradient(top,#65A832 0\%,#5E9C2F 85\%,#5A972C 100\%);background:-o-linear-gradient(top,#65A832 0\%,#5E9C2F 85\%,#5A972C 100\%);color:#FFF;font-size:20px;border-radius:3px 3px 0 0;padding-top:10px}.cform .title:after{content:'';border-top:6px solid #5A972C;border-left:6px solid transparent;border-right:6px solid transparent;display:block;position:absolute;margin:35px 15px}.cform .title span{position:absolute;display:block;text-align:center}.cform .form{background:#FFF;width:100\%;margin:auto;text-align:center;padding:10px 0}.cform .form div{text-align:justify;margin-left:34px;padding:5px 0}#gpio14,#gpio01,#gpio03{padding:5px;outline:none;width:50px;height:25px;border:1px solid #DEDEDE;border-radius:5px;color:#65A832;font-family:'Open Sans',sans-serif;font-size:10px;transition:linear .4s}.cform .form input[type="text"],textarea{padding:5px;outline:none;width:170px;height:20px;border:1px solid #DEDEDE;border-radius:5px;color:#65A832;font-family:'Open Sans',sans-serif;font-size:14px;transition:linear .4s}.cform .form select{padding:5px;outline:none;width:180px;height:30px;border:1px solid #DEDEDE;border-radius:5px;color:#65A832;font-family:'Open Sans',sans-serif;font-size:14px;transition:linear .4s}.cform .form select:focus{height:30px}.cform .form textarea:focus{height:70px}.cform .btn{background:#F3F3F3;text-align:center;border-radius:0 0 3px 3px;border-top:1px solid #EEE;padding:5px}.cform .btn input[type="submit"]{background:#65A832;background:linear-gradient(top,#65A832 0\%,#5E9C2F 85\%,#5A972C 100\%);padding:10px;border:none;border-radius:5px;box-shadow:0 1px 1px #54892C;color:#FFF;cursor:pointer;font-family:'Open Sans',sans-serif})=====";

String workmodehtml = R"=====(<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd"><html><head><meta name="viewport" content="width=device-width,initial-scale=1.0"/> <link href="VictorLozada.css" type="text/css" rel="stylesheet"/><script type="text/javascript"> function booting() { //document.getElementById("workmode").onclick = function () { location.href = "workmode.html"; }; //document.getElementById("wifisetup").onclick = function () { location.href = "wifisetup.html"; }; // document.getElementById("cancel").onclick = function () { location.href = "index.html"; }; }</script></head><body onload="booting()"><form method="post"> <section class="cform"> <article class="title"> <span>GPIO Config</span> </article> <article class="form"> <!-- <img src="sonoff.svg" width="98%" text-align=center /> --> <style type="text/css">.tg {border-collapse:collapse;border-spacing:0;}.tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;}.tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;}.tg .tg-yw4l{vertical-align:top}.tg .tg-baqh{text-align:center;vertical-align:top}select{text-align:center;vertical-align:top;width:25px}option{text-align:center;vertical-align:top;width:25px}</style><div style="width:90%;margin-left:0px;text-align:center"> <table class="tg"> <tr> <th class="tg-yw4l"></th> <th class="tg-yw4l"></th> <th class="tg-yw4l">Switch</th> <th class="tg-yw4l">Button</th> </tr> <tr> <td class="tg-baqh">Relay</td> <td class="tg-baqh">OUT</td> <td class="tg-baqh"></td> <td class="tg-baqh"></td> </tr> <tr> <td class="tg-baqh">Led</td> <td class="tg-baqh">OUT<br></td> <td class="tg-baqh"></td> <td class="tg-baqh"></td> </tr> <tr> <td class="tg-baqh">Button</td> <td class="tg-baqh">IN<br></td> <td class="tg-baqh"><input type="radio" name="gpio00sw" value="switch" %01></td> <td class="tg-baqh"><input type="radio" name="gpio00sw" value="push" %02"></td> </tr> <tr> <td class="tg-baqh">GPIO14<br></td> <td class="tg-baqh"> <select class=rafa id="gpio14" name="gpio14"> <option value="IN" %03>IN</option> <option value="OUT" %04>OUT</option> <option value="NU" %05>N/U</option> </select> </td> <td class="tg-baqh"><input type="radio" name="gpio14sw" value="switch" %06></td> <td class="tg-baqh"><input type="radio" name="gpio14sw" value="push" %07></td> </tr> <tr> <td class="tg-baqh">GPIO01<br></td> <td class="tg-baqh"> <select class=rafa id="gpio01" name="gpio01"> <option value="IN" %08>IN</option> <option value="OUT" %09>OUT</option> <option value="NU" %10>N/U</option> </select> </td> <td class="tg-baqh"><input type="radio" name="gpio01sw" value="switch" %11></td> <td class="tg-baqh"><input type="radio" name="gpio01sw" value="push" %12></td> </tr> <tr> <td class="tg-baqh">GPIO03</td> <td class="tg-baqh"> <select class=rafa id="gpio03" name="gpio03"> <option value="IN" %13>IN</option> <option value="OUT" %14>OUT</option> <option value="NU" %15>N/U</option> </select> </td> <td class="tg-baqh"><input type="radio" name="gpio03sw" value="switch" %16></td> <td class="tg-baqh"><input type="radio" name="gpio03sw" value="push" %17></td> </tr> </table></div> </article> <article class="btn"> <input id="wifisetup" type="submit" name="save" value="Save"><input id="cancel" type="submit" name="cancel" value="Cancel"> </article> </section></form></body></html>)=====";


#endif //TELEPIWEBSERVER_H

