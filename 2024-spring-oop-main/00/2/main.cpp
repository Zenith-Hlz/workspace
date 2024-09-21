#include<iostream>
#include"Book.h"
#include"Library.h"
using namespace std;

int main() {

    Library<int> library;
    Book<int> book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book<int> book2("To Kill a Mockingbird", "Harper Lee", 324);

    library.addBook(book1);
    library.addBook(book2);
    library.show();
    // 此处应该输出:
    // Book name: The Catcher in the Rye, Author: J.D. Salinger, Pages: 277
    // Book name: To Kill a Mockingbird, Author: Harper Lee, Pages: 324

    library.borrowBook("The Catcher in the Rye");
    // 此处应该输出: Books Checked out The Catcher in the Rye.
    
    library.borrowBook("1984");
    // 此处应该输出: Book 1984 does not exist.

    Book<int> book3("1984", "George Orwell", 328);
    if (book2 < book3) book2.show();
    else book3.show();
    // 此处应输出: Book name: To Kill a Mockingbird, Author: Harper Lee, Pages: 324

    return 0;
}
