#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"

template <class T>
class Library {
private:
    std::vector<Book<T>> books;

public:
    void addBook(const Book<T>& book) {
        books.push_back(book);
    }

    void show() const {
        for (const Book<T>& book : books) {
            book.show();
        }
    }

    void borrowBook(const std::string& title) const {
        bool found = false;
        for (const Book<T>& book : books) {
            if (book.getTitle() == title) {
                found = true;
                break;
            }
        }

        if (found) {
            std::cout << "Books Checked out " << title << "." << std::endl;
        } else {
            std::cout << "Book " << title << " does not exist." << std::endl;
        }
    }
};

#endif