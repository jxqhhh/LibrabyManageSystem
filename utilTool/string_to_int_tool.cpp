#include "string_to_int_tool.h"
#include <sstream>
#include <cstdlib>
bool string_to_int_tool::valid(std::string str)
{
    std::stringstream sin(str);
    double d;
    char c;
    if(!(sin >> d)){return false;}
    if (sin >> c){return false;}
    return true;
}

int string_to_int_tool::string_to_int(std::string str)
{
    return atoi(str.c_str());
}

