#include <string>
#include <sstream>

std::string joinArray(char **arr, uint size, std::string seperator = " ", int start = 0, int end = 0)
{
    std::ostringstream oss;
    for (int i = start; i < (end != 0 ? end : size); i++)
    {
        oss << arr[i];
        if (!seperator.empty() && i != size - 1)
            oss << seperator;
    }
    return oss.str();
}

constexpr unsigned int hash(const char *s, int off = 0)
{
    return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}
constexpr unsigned int operator"" _(const char *p, size_t)
{
    return hash(p);
}