#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

class Parser
{
    int num[3] = {1, 2, 3};

public:
    Parser() { return; };
    void add_argument(std::string, int, std::string) { return; };
    void init(char *args);
    int get_argument(std::string s)
    {
        if (s == "first")
            return num[0];
        if (s == "second")
            return num[1];
        if (s == "third")
            return num[2];
        return 0;
    };
};