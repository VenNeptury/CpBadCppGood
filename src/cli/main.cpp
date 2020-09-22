#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include "hash.hpp"
#include "base64.hpp"

std::string formatHelp(char *processName);
void die(std::string message, int exitCode = 0);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        die(formatHelp(argv[0]));
    }

    char *arg = argv[1];

    switch (hash(arg))
    {
    case "help"_:
        die(formatHelp(argv[0]));
    case "uri"_:
        std::cout << "URI!";
        break;
    case "base64"_:
    case "b64"_:
    {
        if (argc < 4)
            die("Too little arguments!");

        char *action = argv[2];
        std::string rest;
        if (argc == 4)
            rest = argv[3];
        else
        {
            std::ostringstream oss;
            for (int i = 3; i < argc; i++)
                oss << argv[i] << ' ';
            rest = oss.str();
        }

        if (strcmp(action, "d") == 0)
        {
            std::string out;
            std::string decodeRes = macaron::Base64::Decode(rest, out);
            if (!decodeRes.empty())
                die(decodeRes);
            die(out);
        }
        else if (strcmp(action, "e") == 0)
        {
            die(macaron::Base64::Encode(rest));
        }
        else
        {
            std::ostringstream oss;
            oss << "Invalid argument \"" << action << "\". Valid options: [e|d]";
            die(oss.str(), 1);
        }
        break;
    }
    default:
    {
        std::ostringstream oss;
        oss << "Invalid Input \"" << arg << "\" \n\n"
            << formatHelp(argv[0]);
        die(oss.str(), 1);
    }
    }

    return 0;
}

void die(std::string message, int exitCode)
{
    std::cout << message << '\n';
    exit(exitCode);
}

std::string formatHelp(char *processName)
{
    std::ostringstream oss;
    oss << "usage:  " << processName << " <operation> [...]\noperations:";
    for (auto line : {"help", "uri"})
        oss << "\n\t" << processName << " " << line;

    return oss.str();
}