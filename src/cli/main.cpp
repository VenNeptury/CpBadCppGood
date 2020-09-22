#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include "hash.hpp"
#include "base64.hpp"

const std::string formatHelp(char *processName);
void die(std::string message, int exitCode = 0);
void handleBase64(int argc, char **argv);

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
        handleBase64(argc, argv);
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

const std::string formatHelp(char *processName)
{
    std::ostringstream oss;
    oss << "usage:  " << processName << " <operation> [...]\noperations:";
    for (auto line : {"help", "uri"})
        oss << "\n\t" << processName << " " << line;

    return oss.str();
}

void handleBase64(int argc, char **argv)
{
    if (argc < 3)
        die("Too few arguments!");

    char *action = argv[2];
    bool skippedAction = false;
    std::string rest = "";
    if (std::strcmp(action, "d") != 0 && std::strcmp(action, "e") != 0)
    {
        skippedAction = true;
    }
    else if (argc == 3)
        die("Too few arguments!");

    if (argc > (skippedAction ? 3 : 4))
    {
        std::ostringstream oss;
        for (int i = skippedAction ? 2 : 3; i < argc; i++)
            oss << argv[i] << ' ';
        rest += oss.str();
    }
    else
        rest += argv[argc - 1];

    if (std::strcmp(action, "d") == 0)
    {
        std::string out;
        std::string decodeRes = macaron::Base64::Decode(rest, out);
        if (!decodeRes.empty())
            die(decodeRes);
        die(out);
    }
    else if (skippedAction || std::strcmp(action, "e") == 0)
    {
        die(macaron::Base64::Encode(rest));
    }
    else
    {
        std::ostringstream oss;
        oss << "Invalid argument \"" << action << "\". Valid options: [e|d]";
        die(oss.str(), 1);
    }
}