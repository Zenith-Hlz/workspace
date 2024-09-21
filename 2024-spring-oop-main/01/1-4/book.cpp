#include "book.h"

Book::Book(int ID, std::string name, std::string author, std::string publishing_house)
{
    this->ID = ID;
    this->name = name;
    this->author = author;
    this->publishing_house = publishing_house;
}

int Book::get_ID() { return ID; }
string Book::get_name() { return name; }
string Book::get_author() { return author; }
string Book::get_publishing_house() { return publishing_house; }
bool Book::get_state() { return state.first; }
void Book::change_state()
{ // 1ÊÇÒÑ½è³ö
    state.first = !state.first;
}
void Book::change_state(string name)
{
    state.second = name;
}
void Book::print_message()
{
    std::cout << "ID:" << ID << '\n';
    std::cout << "name:" << name << '\n';
    std::cout << "author:" << author << '\n';
    std::cout << "publishing_house:" << publishing_house << '\n';
    if (state.first)
    {
        std::cout << "borrower:" << state.second << '\n';
        std::cout << "state:borrowed" << '\n';
    }
    else
        std::cout << "state:loanable" << '\n';
}