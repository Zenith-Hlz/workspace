#include "editor.h"
#include <iostream>
#include <sstream>
#include <algorithm>

TextEditor::TextEditor()
{
    data.push_back("");
    cursor = {0, 0};
}

void TextEditor::saveState()
{
    history.push_back({data, cursor});
}

void TextEditor::move(Position dest)
{
    cursor.first = std::max(0, std::min(dest.first, (int)data.size() - 1));
    cursor.second = std::max(0, std::min(dest.second, (int)data[cursor.first].size()));
}

void TextEditor::write(const std::string &str)
{
    saveState();
    data[cursor.first].insert(cursor.second, str);
    cursor.second += str.size();
}

void TextEditor::newline()
{
    saveState();
    std::string newLine = data[cursor.first].substr(cursor.second);
    data[cursor.first] = data[cursor.first].substr(0, cursor.second);
    data.insert(data.begin() + cursor.first + 1, newLine);
    cursor.first++;
    cursor.second = 0;
}

void TextEditor::del()
{
    if (cursor.first == 0 && cursor.second == 0)
        return;
    saveState();
    if (cursor.second > 0)
    {
        data[cursor.first].erase(cursor.second - 1, 1);
        cursor.second--;
    }
    else
    {
        cursor.second = data[cursor.first - 1].size();
        data[cursor.first - 1] += data[cursor.first];
        data.erase(data.begin() + cursor.first);
        cursor.first--;
    }
}

void TextEditor::undo()
{
    if (!history.empty())
    {
        auto lastState = history.back();
        history.pop_back();
        data = lastState.first;
        cursor = lastState.second;
    }
}

void TextEditor::screenShot() const
{
    std::cout << "### SCREENSHOT BEGIN ###" << std::endl;
    for (int i = 0; i < data.size(); ++i)
    {
        if (i == cursor.first)
        {
            std::cout << data[i].substr(0, cursor.second) << '*' << data[i].substr(cursor.second) << std::endl;
        }
        else
        {
            std::cout << data[i] << std::endl;
        }
    }
    std::cout << "### SCREENSHOT END ###" << std::endl;
}

void TextEditor::apply(const std::string &cmd)
{
    std::istringstream iss(cmd);
    std::string opt;
    iss >> opt;

    if (opt == "MOVE")
    {
        int row, col;
        iss >> row >> col;
        move({row, col});
    }
    else if (opt == "WRITE")
    {
        std::string text;
        iss >> text;
        write(text);
    }
    else if (opt == "NEWLINE")
    {
        newline();
    }
    else if (opt == "DELETE")
    {
        del();
    }
    else if (opt == "UNDO")
    {
        undo();
    }
    else if (opt == "SCREEN")
    {
        screenShot();
    }
}