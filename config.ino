#include <ESP8266WiFi.h>
// #include <WiFiClient.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

// #include <WiFiUdp.h>
#include <FS.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>

#include "config.h"

Conf::Conf() {
  variables = "";
  load();
}
bool Conf::load() {
  File configFile = SPIFFS.open("/config.txt", "r");
  if (!configFile) return false;
  variables = configFile.readString();
  configFile.close();
  variables.trim();
  variables.replace("\r", "\n");
  variables.replace("\n\n", "\n");
  return true;
}
bool Conf::save() {
  File configFile = SPIFFS.open("/config.txt", "w");
  if (!configFile) return false;
  configFile.print(variables);
  configFile.close();
  return true;
}
String Conf::getConfig() {
  return variables;
}
void Conf::setConfig(String vars) {
  variables = vars;
}
void Conf::addConfig(String varname, String varval) {
  variables = variables + varname + "=>" + varval + "\r\n";
}
String Conf::getFirstVar(String *text, String separator) {
  int8_t pos = text->indexOf(separator);
  if (pos == -1) return (*text);
  String first = text->substring(0, pos);
  *text = text->substring(pos + 1);
  text->trim();
  first.trim();
  return first;
}
String Conf::getVariable(String varname,String defval) {
  String res=getVariable(varname);
  if (res=="") addConfig(varname,defval);
  else return res;
  return defval;
}
String Conf::getVariable(String varname) {
  int8_t pos = variables.indexOf(varname + equal);
  if (pos == -1) return ("");
  String first = variables.substring(pos + varname.length() + equal.length());
  pos = first.indexOf("\n");
  first = first.substring(0, pos);
  first.trim();
  return first;
}
char* Conf::getVariableChar(String varname) {
  return (char *)varname.c_str();
}
