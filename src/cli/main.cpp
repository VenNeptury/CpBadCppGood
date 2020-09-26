#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include "uri_encode.hpp"
#include "base64.hpp"
#include "string_helpers.hpp"

std::string formatHelp(char *processName);
void die(const std::string &message, int exitCode = 0);
void handleBase64(int argc, char **argv);
void handleRepeat(int argc, char **argv);
void handleAlternate(int argc, char **argv);
void handleUri(int argc, char **argv);
void handleGoogle(int argc, char **argv, bool img = false);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        die(formatHelp(argv[0]));
    }

    char *arg = argv[1];
    char *args[argc - 2];
    for (int i = 2; i < argc; i++)
    {
        args[i - 2] = argv[i];
    }
    argc -= 2;

    switch (hash(arg))
    {
    case "help"_:
        die(formatHelp(argv[0]));
    case "uri"_:
        handleUri(argc, args);
    case "google"_:
        handleGoogle(argc, args);
    case "googleimg"_:
        handleGoogle(argc, args, true);
    case "tweet"_:
        if (!argc)
            die("Too few arguments");
        die("https://twitter.com/compose/tweet?text=" + encodeURIComponent(joinArray(args, argc)));
    case "base64"_:
    case "b64"_:
        handleBase64(argc, args);
    case "repeat"_:
        handleRepeat(argc, args);
    case "reverse"_:
    {
        std::string input = joinArray(args, argc);
        std::reverse(input.begin(), input.end());
        die(input);
    }
    case "alternate"_:
        handleAlternate(argc, args);
    case "titlecase"_:
        die(toTitleCase(joinArray(args, argc)));
    default:
    {
        std::ostringstream oss;
        oss << "Invalid input \"" << arg << "\" \n\n"
            << formatHelp(argv[0]);
        die(oss.str(), 1);
    }
    }

    return 0;
}

void die(const std::string &message, int exitCode)
{
    std::cout << message << '\n';
    exit(exitCode);
}

std::string formatHelp(char *processName)
{
    std::ostringstream oss;
    oss << "usage:  " << processName << " <operation> [...]\noperations:";
    for (auto line : {
             "help",
             "base64 <[e]ncode|[d]ecode> <text...>",
             "uri <[e]ncode|[e]decode> <text...>",
             "google <text...>",
             "googleimg <text...>",
             "tweet <text...>",
             "repeat <n> <text...>",
             "alternate <text...>",
             "titlecase <text...>"})
        oss << "\n\t" << processName << " " << line;

    return oss.str();
}

void handleUri(int argc, char **argv)
{
    if (argc < 1)
        die("Too few arguments!");

    char *action = argv[0];
    bool skippedAction = false;
    if (std::strcmp(action, "d") != 0 && std::strcmp(action, "e") != 0)
    {
        skippedAction = true;
    }
    else if (argc == 1)
        die("Too few arguments!");

    std::string rest = joinArray(argv, argc, " ", skippedAction ? 0 : 1);
    if (skippedAction || std::strcmp(action, "e") == 0)
        die(encodeURIComponent(rest));
    die(decodeURIComponent(rest));
}

void handleBase64(int argc, char **argv)
{
    if (argc < 1)
        die("Too few arguments!");

    char *action = argv[0];
    bool skippedAction = false;
    std::string rest;
    if (std::strcmp(action, "d") != 0 && std::strcmp(action, "e") != 0)
    {
        skippedAction = true;
    }
    else if (argc == 1)
        die("Too few arguments!");

    if (argc > (skippedAction ? 1 : 2))
    {
        rest += joinArray(argv, argc, " ", skippedAction ? 0 : 1);
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

void handleRepeat(int argc, char **argv)
{
    if (argc < 2)
        die("Too few arguments!");

    int times;
    try
    {
        times = std::stoi(argv[0]);
    }
    catch (std::exception const &e)
    {
        die("You did not provide a valid number for how many times the string should be repeated.");
    }

    std::string sentence = joinArray(argv, argc, " ", 1);

    std::string output;
    output.reserve(sentence.size() * times);
    while (times--)
        output += sentence;
    die(output);
}

void handleAlternate(int argc, char **argv)
{
    if (argc < 1)
        die("Too few arguments!");

    std::string output;
    bool alternated = false;

    for (int i = 0; i < argc; i++)
    {
        std::string word = argv[i];
        std::string alternatedWord;
        for (int j = 0; j < word.size(); j++)
        {
            alternatedWord += alternated ? toupper(word.at(j)) : tolower(word.at(j));
            alternated = !alternated;
        }
        output += alternatedWord;
        if (i != argc - 1)
            output += ' ';
    }

    die(output);
}

void handleGoogle(int argc, char **argv, bool img)
{
    if (!argc)
        die("Too few arguments");
    die("https://www.google.com/search?" + std::string(img ? "tbm=isch&q=" : "q=") + encodeURIComponent(joinArray(argv, argc)));
}
