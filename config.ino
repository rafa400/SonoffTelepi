#include <FS.h>

#include "config.h"

Conf::Conf() {
  variables = " ";
  load();
  maxv=0;
}
bool Conf::load() {
  File configFile = SPIFFS.open("/config.txt", "r");
  maxv=0;
  if (!configFile) return false;
  while ((maxv<pair_max) && (configFile.available()>0)) {
    myvar[maxv].variable=configFile.readBytesUntil(':');
    myvar[maxv].value=configFile.readBytesUntil('\n');
    maxv++;
  }
  configFile.close();
  return true;
}
bool Conf::save() {
  File configFile = SPIFFS.open("/config.txt", "w");
  if (!configFile) return false;
  for(int i=0;i<maxv;i++) {
    configFile.print(myvar[i].variable+":");
    configFile.print(myvar[i].valor+"\n");
  }
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
  if (pos == -1) {String first=*text; return ("");}
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
  int8_t pos = variables.indexOf(varname + equ);
  if (pos == -1) return ("");
  String first = variables.substring(pos + varname.length() + equ.length());
  pos = first.indexOf("\n");
  first = first.substring(0, pos);
  first.trim();
  return first;
}
char* Conf::getVariableChar(String varname) {
  return (char *)varname.c_str();  // ESTA MAL , NO DEVUELVE VALOR
}


