#ifndef TELEPICONFIG_H
#define TELEPICONFIG_H

#include <FS.h>

// ******************************************************************************************************
// **       Config management        **
// ************************************
class Conf {
  public:
    Conf();
    bool load();
    bool save();
    String getConfig();
    void setConfig(String vars);
    void addConfig(String varname, String varval);
    static String getFirstVar(String *text, String separator);
    String getVariable(String varname);
    String getVariable(String varname, String defval);
    char* getVariableChar(String varname);
  private:
    String variables;
    const String equal = "=>";
};

#endif //TELEPICONFIG_H
