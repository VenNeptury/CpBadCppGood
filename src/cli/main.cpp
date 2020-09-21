#include <iostream>
#include <string>
#include "hash.hpp"

void printHelp(char *processName);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printHelp(argv[0]);
        return 0;
    }

    char *arg = argv[1];

    switch (hash(arg))
    {
    case "help"_:
        printHelp(argv[0]);
        break;
    case "uri"_:
        std::cout << "URI!";
        break;
    default:
        std::cout << "Invalid Input \"" << arg << "\" \n\n";
        printHelp(argv[0]);
    }

    return 0;
}

void printHelp(char *processName)
{
    std::cout << "usage:  " << processName << " <operation> [...]\noperations:";
    for (auto line : {"help", "uri"})
        std::cout << "\n\t" << processName << " " << line;
    std::cout << '\n';
}