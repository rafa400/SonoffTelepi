#ifndef TELEPICONFIG_H
#define TELEPICONFIG_H

#include <FS.h>
#include "MD5.h"
#include <ESP8266WebServer.h>

// ******************************************************************************************************
// **       Config management        **
// ************************************

#define pair_max 40  // Max number of variables
#define l_max 40     // Max length of variables

struct pair {
   char variable[l_max+1];
   char value[l_max+1];
};


class Conf {
  public:
    Conf();
    bool load();
    bool save();
    bool savedef();
    bool reset();
    String readConfig();
    void addConfig(String varname, String varval);
    String getVariable(String varname);
    String getVariable(String varname, String defval);
    String setVariable(String varname, String defval);
    bool checkUserPassword(String user,String password);
    bool checkUserMD5Password(String user,String password);
    void setUserPassword(String user,String password);
    static String getFirstVar(String *text, String separator);
    bool setArgs(ESP8266WebServer &WebServer);
  private:
    pair myvar[pair_max+1];
    int maxv;
};

const char configuration[] PROGMEM = R"=====(wifiSSID:KITIPASA
wifipassword:<kitipasa>
Wifi_IP:192.168.2.224
Wifi_GW:192.168.2.9
Wifi_MSK:255.255.255.0
Wifi_DNS:8.8.8.8
hostname:ESP8266RAFA2
gpio00:IN-R
gpio13:Pulse
gpio00sw:push
gpio14:IN-R
gpio14sw:switch
gpio01:NU
gpio01sw:switch
gpio03:NU
gpio03sw:switch
save:Save
user_admin:21232f297a57a5a743894a0e4a801fc3
wifimode:CLI
dhcp:FIXIP)=====";


#endif //TELEPICONFIG_H
