
#include "SharedFunctions.h"
#include <string>
#include <iostream>
bool isInteger(const std::string & s)
{
   if(s.empty() || ((!isdigit(s[0])))) return false;// && (s[0] != '+'))) return false ;

   char * p ;
   strtol(s.c_str(), &p, 10) ;

   return (*p == 0) ;
}

std::string escapeDoubleQuotes(const std::string & s) {
    if(s[0]=='"') { 
       return "\\"+s.substr(0, s.size()-1)+"\\\"";
    }
    return s;
}

bool isVariable(const std::string & v) {
    return (v[0] >= 'A' && v[0] <= 'Z');

}
