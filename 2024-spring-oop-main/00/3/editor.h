#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include <string>

class TextEditor {
private:
    using Position = std::pair<int, int>;
    std::vector<std::string> data;
    Position cursor;
    std::vector<std::pair<std::vector<std::string>, Position>> history;

    void saveState();

public:
    TextEditor();
    void move(Position dest);
    void write(const std::string& str);
    void newline();
    void del();
    void screenShot() const;
    void undo();
    void apply(const std::string& opt);
};

#endif // EDITOR_H
