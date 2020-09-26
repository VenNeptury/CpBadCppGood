#ifndef _STRING_HELPERS_H_
#define _STRING_HELPERS_H_

#include <string>
#include <sstream>

const std::string joinArray(char **arr, int size, const std::string &seperator = " ", int start = 0, int end = -1)
{
    bool sepExists = !seperator.empty();
    std::ostringstream oss;
    for (int i = start; i < (end != -1 ? end : size); i++)
    {
        oss << arr[i];
        if (sepExists)
            oss << seperator;
    }
    std::string str{oss.str()};
    str.pop_back();
    return str;
}

constexpr unsigned int hash(const char *s, int off = 0)
{
    return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}
constexpr unsigned int operator"" _(const char *p, size_t)
{
    return hash(p);
}

#endif