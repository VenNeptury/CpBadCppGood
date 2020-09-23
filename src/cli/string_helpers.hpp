#include <string>
#include <sstream>

std::string joinArray(char **arr, int size, std::string seperator = "", int start = 0, int end = 0)
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