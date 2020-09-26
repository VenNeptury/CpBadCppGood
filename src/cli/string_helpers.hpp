#ifndef _STRING_HELPERS_H_
#define _STRING_HELPERS_H_

#include <string>
#include <sstream>
#include <regex>

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

const std::string toLowerCase(std::string str)
{
    std::ostringstream oss;
    for (auto &x : str)
        oss << (islower(x) ? char(x) : char(tolower(x)));

    std::string output = oss.str();
    return output;
}

const std::string toUpperCase(std::string str)
{
    std::ostringstream oss;
    for (auto &x : str)
        oss << (isupper(x) ? char(x) : char(toupper(x)));

    std::string output = oss.str();
    return output;
}

const std::string toTitleCase(std::string str, char seperator = ' ')
{
    using namespace std;
    istringstream iss(str);
    ostringstream oss;
    string segment;

    while (getline(iss, segment, seperator))
    {
        if (segment.empty())
            continue;

        oss << toUpperCase({segment[0]}) << toLowerCase(segment.substr(1)) << seperator;
    }
    segment = oss.str();
    segment.pop_back();

    return segment;
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
