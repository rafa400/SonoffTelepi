#include <FS.h>

#include "config.h"

Conf::Conf() {
  load();
}
bool Conf::load() {
  // savedef();
  SPIFFS.begin();
  File configFile = SPIFFS.open("/config1.txt", "r");
  maxv=0;
  int n1,n2;
  if (!configFile) return false;
  while ((maxv<pair_max) && (configFile.available()>0)) {
    n1=configFile.readBytesUntil(':',myvar[maxv].variable,l_max);
    myvar[maxv].variable[n1]=0;
    n2=configFile.readBytesUntil('\n',myvar[maxv].value,l_max);
    myvar[maxv].value[n2]=0;
    if (n1>0 && n2>0)  maxv++;  // Will not load if value is empty
  }
  configFile.close();
  SPIFFS.end();
  return true;
}
bool Conf::save() {
  SPIFFS.begin();
  File configFile = SPIFFS.open("/config1.txt", "w");
  if (!configFile) return false;
  for(int i=0;i<maxv;i++) {
    configFile.print(String(myvar[i].variable)+":");
    configFile.print(String(myvar[i].value)+"\n");
  }
  configFile.close();
  SPIFFS.end();
  return true;
}

bool Conf::savedef() {
  maxv=0;
  getVariable("hostname",HOSTNAME + String(ESP.getChipId(), HEX));
  getVariable("wifiSSID","KITIPASAa");
  getVariable("wifipassword","kitipasa");
  getVariable("Wifi_IP","192.168.0.20");
  getVariable("Wifi_GW","192.168.0.1");
  getVariable("Wifi_MSK","255.255.255.0");
  getVariable("Wifi_DNS","8.8.8.8");
  getVariable("user_admin","21232f297a57a5a743894a0e4a801fc3");
  getVariable("wifimode","AP");
  getVariable("dhcp","DHCP");
  getVariable("gpio00","IN-R");
  getVariable("gpio13","Pulse");
  getVariable("gpio00sw","push");
  getVariable("gpio14","IN-R");
  getVariable("gpio14sw","switch");
  getVariable("gpio01","NU");
  getVariable("gpio01sw","switch");
  getVariable("gpio03","NU");
  getVariable("gpio03sw","switch");
  getVariable("MQTTenabled","off");
  getVariable("MQTTServerPath","TelePi/Sonoff");
  getVariable("MQTT_IP","192.168.0.1");
  getVariable("MQTT_Port","1883");
  getVariable("MQTTpassword","telepi");
  getVariable("IFTTTenabled","off");
  getVariable("IFTTTevent","");
  getVariable("IFTTTkey","");
  getVariable("ext1sw","switch");
  getVariable("ext1IP","");
  getVariable("ext1dest","Disabled");
  getVariable("ext2sw","switch");
  getVariable("ext2IP","");
  getVariable("ext2dest","Disabled");
  getVariable("ext3sw","switch");
  getVariable("ext3IP","");
  getVariable("ext3dest","Disabled");
  getVariable("ext4sw","switch");
  getVariable("ext4IP","");
  getVariable("ext4dest","Disabled");
  SPIFFS.format();
  SPIFFS.begin();
  SPIFFS.end();
  save();
  return true;
}

bool Conf::reset() {
  maxv=0;
  save();
}
String Conf::readConfig() {
  SPIFFS.begin();
  File configFile = SPIFFS.open("/config1.txt", "r");
  String content = "EMPTY!";
  if (configFile) content = configFile.readString();
  configFile.close();
  SPIFFS.end();
  return content;
}

void Conf::addConfig(String varname, String varval) {
  myvar[maxv].variable[0]=0; myvar[maxv].value[0]=0;
  if (varname!=NULL && varname!="") strcpy(myvar[maxv].variable,varname.c_str());
  if (varval!=NULL && varval!="")  strcpy(myvar[maxv].value,varval.c_str());
  maxv++;
}
String Conf::getFirstVar(String &text, String separator) {
  int8_t pos = text.indexOf(separator);
  if (pos == -1) {String first=text;text=""; return (first);}
  String first = text.substring(0, pos);
  text = text.substring(pos + 1);
  text.trim();
  first.trim();
  return first;
}
String Conf::getVariable(String varname,String defval) {
  int i=0;  
  while (i<maxv) {
    if (varname==String(myvar[i].variable)) return String(myvar[i].value);
    i++;
  }
  addConfig(varname,defval);
  return defval;
}
String Conf::getVariable(String varname) {
  int i=0;
  while (i<maxv) {
    if (varname==String(myvar[i].variable)) return String(myvar[i].value);
    i++;
  }
  return "";
}
String Conf::setVariable(String varname,String defval) {
  int i=0;
  while (i<maxv) {
    String kk=String(myvar[i].variable);
    varname.trim();
    defval.trim();
    if (varname==kk) {
       if ((defval==NULL) || (defval==""))
         {myvar[i].value[0]=0;myvar[i].value[1]=0;}
       else
         strcpy(myvar[i].value,defval.c_str());
       return defval;
    }
    i++;
  }
  addConfig(varname, defval);
  return defval;
}

bool Conf::checkUserPassword(String user,String password){
  char passwd[35]; // Max MD5 typically 32 hex digits
  strcpy(passwd,password.c_str());
  unsigned char* hash=MD5::make_hash(passwd);
  char *md5str = MD5::make_digest(hash, 16);
  free(hash);
  return (getVariable("user_"+user)==String(md5str)?true:false);
}
bool Conf::checkUserMD5Password(String user,String md5password){
  return (getVariable("user_"+user)==md5password?true:false);
}

void Conf::setUserPassword(String user,String password){
  char passwd[35]; // Max MD5 typically 32 hex digits
  strcpy(passwd,password.c_str());
  unsigned char* hash=MD5::make_hash(passwd);
  char *md5str = MD5::make_digest(hash, 16);
  free(hash);
  setVariable("user_"+user,String(md5str));
}
bool Conf::setArgs(ESP8266WebServer &WebServer) {
  //String content = " ";  // Meter un espacio en blanco en sprintf cuelga!!
  if (WebServer.args() > 0 ) {
    for ( uint8_t j = 0; j < WebServer.args(); j++ ) {
      if(WebServer.argName(j)=="cancel") return false;
      if(WebServer.argName(j)=="save") {
        if (WebServer.args() > 0 ) {
          uint8_t i;
          for ( i = 0; i < WebServer.args(); i++ ) {
              //content = content + "\r\n" + WebServer.argName(i) + "--" + WebServer.arg(i);
              setVariable(WebServer.argName(i),WebServer.arg(i));
          }
          setVariable("count",String(i));
          setVariable("maxv",String(maxv));
          setUserPassword("admin","admin");
          save();
          return true;
        }
      }
    }
  }
  return true;
}

