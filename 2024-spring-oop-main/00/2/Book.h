#ifndef BOOK_H
#define BOOK_H

#include <iostream>

template <class T>
class Book {
private:
    std::string title;
    std::string author;
    T pages;

public:
    Book(const std::string& title, const std::string& author, const T& pages) : title(title), author(author), pages(pages) {}

    std::string getTitle() const {
        return title;
    }

    void show() const {
        std::cout << "Book name: " << title << ", Author: " << author << ", Pages: " << pages << std::endl;
    }

    bool operator<(const Book<T>& other) const {
        return pages < other.pages;
    }
};

#endif