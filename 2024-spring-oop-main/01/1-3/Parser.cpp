#include "Parser.h"

bool there_is_help(std::vector<std::string> arg)
{
    for (std::string mem : arg)
    {
        if (mem == "--help")
            return 1;
    }
    return 0;
}
bool isnumber(std::string s)
{
    for (char mem : s)
    {
        if (mem < '0' || mem > '9')
            return 0;
    }
    return 1;
}

void help_message()
{
    std::cout << "usage: ./main [--help] [--first FIRST] [--second SECOND] [--third THIRD]\n";
    std::cout << "\n";
    std::cout << "optional arguments:\n";
    std::cout << "--help   show this help message and exit\n";
    std::cout << "--first FIRST   First number\n";
    std::cout << "--second SECOND   Next number\n";
    std::cout << "--third THIRD   Third number\n";
}

void wrong1(std::string s)
{
    std::cout << "usage: ./main [--help] [--first FIRST] [--second SECOND] [--third THIRD]\n";
    std::cout << "./main: error: unrecognized arguments: ";
    std::cout << s;
    exit(0);
}
void wrong2(std::string s)
{
    std::cout << "usage: ./main [--help] [--first FIRST] [--second SECOND] [--third THIRD]\n";
    std::cout << "./main: error: argument ";
    std::cout << s;
    std::cout << ": expected an argument";
    exit(0);
}
void wrong3(std::string s, std::string s1)
{
    std::cout << "usage: ./main [--help] [--first FIRST] [--second SECOND] [--third THIRD]\n";
    std::cout << "./main: error: argument ";
    std::cout << s;
    std::cout << ": invalid int value: '";
    std::cout << s1 << '\'';
    exit(0);
}
bool valid(std::string s)
{
    if (s == "--first" || s == "--second" || s == "--third")
        return 1;
    else
        return 0;
}
void Parser::init(char *args)
{
    std::stringstream ss(args);
    std::string word;
    std::vector<std::string> arg;

    while (ss >> word)
    {
        arg.push_back(word);
    }

    if (there_is_help(arg))
    {
        help_message();
        exit(0);
    }
    else
    {
        for (auto iter = arg.begin(); iter != arg.end(); iter++)
        {
            if (!valid(*iter))
                wrong1(*iter);
            else if (iter + 1 == arg.end())
                wrong2(*iter);
            else if (!isnumber(*(iter + 1)))
                wrong3(*iter, *(iter + 1));
            else
            {
                if (*iter == "--first")
                    num[0] = std::stoi(*(iter + 1));
                if (*iter == "--second")
                    num[1] = std::stoi(*(iter + 1));
                if (*iter == "--third")
                    num[2] = std::stoi(*(iter + 1));
                iter++;
            }
        }
    }
}