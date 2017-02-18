#include <FS.h>

#include "config.h"

Conf::Conf() {
  load();
}
bool Conf::load() {
  SPIFFS.begin();
  File configFile = SPIFFS.open("/config.txt", "r");
  maxv=0;
  int n;
  if (!configFile) return false;
  while ((maxv<pair_max) && (configFile.available()>0)) {
    n=configFile.readBytesUntil(':',myvar[maxv].variable,l_max);
    myvar[maxv].variable[n-1]=0;
    n=configFile.readBytesUntil('\n',myvar[maxv].value,l_max);
    myvar[maxv].value[n-1]=0;
    maxv++;
  }
  configFile.close();
  SPIFFS.end();
  return true;
}
bool Conf::save() {
  SPIFFS.begin();
  File configFile = SPIFFS.open("/config.txt", "w");
  if (!configFile) return false;
  for(int i=0;i<maxv;i++) {
    configFile.print(String(myvar[i].variable)+":");
    configFile.print(String(myvar[i].value)+"\n");
  }
  configFile.close();
  SPIFFS.end();
  return true;
}
bool Conf::reset() {
  maxv=0;
  save();
}
String Conf::readConfig() {
  SPIFFS.begin();
  File configFile = SPIFFS.open("/config.txt", "r");
  String content = "EMPTY!";
  if (configFile) content = configFile.readString();
  configFile.close();
  SPIFFS.end();
  return content;
}

void Conf::addConfig(String varname, String varval) {
  strcpy(myvar[maxv].variable,varname.c_str());
  strcpy(myvar[maxv].value,varval.c_str());
  maxv++;
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
    if (varname==String(myvar[i].variable)) {
       strcpy(myvar[i].value,defval.c_str());
       return defval;
    }
    i++;
  }
  addConfig(varname, defval);
  return defval;
}

char* Conf::getVariableChar(String varname) {
  return (char *)varname.c_str();  // ESTA MAL , NO DEVUELVE VALOR
}


