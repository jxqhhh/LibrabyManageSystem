#ifndef STRING_TO_INT_TOOL_H
#define STRING_TO_INT_TOOL_H

#include <string>

class string_to_int_tool
{
public:
    static bool valid(std::string str);//判断字符串是否为数字
    static int string_to_int(std::string str);
};

#endif // STRING_TO_INT_TOOL_H
