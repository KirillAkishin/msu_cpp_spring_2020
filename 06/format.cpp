#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <exception>

#include "format.h"
 

std::string format(const std::string& str)
{
    return str;
}

std::string format(const std::string& str, const std::vector<std::string>& arr)
{
    std::string result, buffer;
    size_t n;
    char c;
    bool cnd = false, last;
    for (size_t i = 0; i <= str.size(); ++i)
    {
        last = (i == str.size());
        c = str[i];
        if (cnd)
        {
            if (isdigit(c))
                buffer += c;
            else
            {
                if (c == '}')
                    cnd = false;
                else
                    throw std::runtime_error("error");
                n = 0;
                if (!buffer.empty())
                    n = atoi(buffer.c_str());
                if (n >= 0 && n < arr.size())
                    result += arr[n];
                else
                    throw std::runtime_error("error");
                buffer.clear();
            }
        }
        else
        {
            if (c == '{')
            {
                cnd = true;
            }
            else if (c == '}')
            {
                throw std::runtime_error("error");
            }
            else
            {
                if (!last)
                    result += c;
            }
        }
    }
    return result;
}