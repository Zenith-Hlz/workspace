#include "library.h"

void Library::add_book(Book book)
{
    std::cout << "Added:" << book.get_name() << '\n';
    Books.push_back(book);
    return;
}
void Library::delete_book(int book_ID)
{
    for (auto iter = Books.begin(); iter != Books.end(); iter++)
    {
        if ((*iter).get_ID() == book_ID)
        {
            std::cout << "Deleted:" << (*iter).get_name() << '\n';
            Books.erase(iter);
            return;
        }
    }
    std::cout << "Delete Failed\n";
    return;
}
void Library::find_book(int book_ID)
{
    for (auto iter = Books.begin(); iter != Books.end(); iter++)
    {
        if ((*iter).get_ID() == book_ID)
        {
            (*iter).print_message();
            return;
        }
    }
    std::cout << "Find Failed\n";
    return;
}
void Library::borrow_book(int book_ID, string borrower)
{
    for (auto iter = Books.begin(); iter != Books.end(); iter++)
    {
        if ((*iter).get_ID() == book_ID)
        {
            std::cout << "Borrowed:" << (*iter).get_name() << '\n';
            (*iter).change_state();
            (*iter).change_state(borrower);
            return;
        }
    }
    std::cout << "Borrow Failed\n";
    return;
}
void Library::return_book(int book_ID)
{
    for (auto iter = Books.begin(); iter != Books.end(); iter++)
    {
        if ((*iter).get_ID() == book_ID)
        {
            std::cout << "Returned:" << (*iter).get_name() << '\n';
            (*iter).change_state();
            return;
        }
    }
    std::cout << "Return Failed\n";
    return;
}