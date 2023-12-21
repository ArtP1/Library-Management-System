#include <iostream>
#include <cassert>
#include <map>
#include "Book.h"
#include "Shelf.h"
#include "Reader.h"
using namespace std;

int main() {
    Reader reader = Reader(1, "Jaime Palacios", "(831)-208-0297");
    Book book = Book("The Great Gatsby", "F. Scott Fitzgerald", 1925, "978-0-743-27356-5", "Fiction");
    // cout << reader.getName() << endl;
    // reader.checkOutBook(book);
    // reader.returnBook(book);
    // reader.hasBook(book);
    
}