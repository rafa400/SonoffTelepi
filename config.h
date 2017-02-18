#ifndef TELEPICONFIG_H
#define TELEPICONFIG_H

#include <FS.h>

// ******************************************************************************************************
// **       Config management        **
// ************************************

#define pair_max 20  // Max number of variables
#define l_max 30     // Max length of variables

struct pair {
   char variable[l_max+1];
   char value[l_max+1];
};


class Conf {
  public:
    Conf();
    bool load();
    bool save();
    bool reset();
    String readConfig();
    void addConfig(String varname, String varval);
    String getVariable(String varname);
    String getVariable(String varname, String defval);
    String setVariable(String varname, String defval);
    char* getVariableChar(String varname);
    static String getFirstVar(String *text, String separator);
  private:
    pair myvar[pair_max+1];
    int maxv;
};

#endif //TELEPICONFIG_H
