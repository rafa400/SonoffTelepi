#ifndef TELEPICONFIG_H
#define TELEPICONFIG_H

#include <FS.h>

// ******************************************************************************************************
// **       Config management        **
// ************************************

#define pair_max 20  // Max number of variables

struct pair {
   String variable;
   String value;
};


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
    pair myvar[pair_max+1];
    String variables;
    const String equ = "=>";
    int maxv;
};

#endif //TELEPICONFIG_H
