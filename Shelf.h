#ifndef SHELF_H
#define SHELF_H

#include <iostream>
#include <unordered_map>
#include "Book.h"
using namespace std;

class Shelf {
  public:
    Shelf();
    Shelf(int shelf_num, string subject);

    // setters & getters
    int getShelfNumber() const {return shelf_num;}
    string getSubject() const {return subject;}
    int getTotalBookCount() const {return books.size();}
    int getBookCount(const Book& target_book);
    void setShelfNumber(int shelf_num) {this->shelf_num = shelf_num;}
    void setSubject(string subject) {this->subject = subject;}
    

    // other(s)
    void addBook(const Book& new_book);
    void removeBook(const Book& target_book);
    void listBooks();

  private:
    int shelf_num;
    string subject;
    unordered_map<Book, int> books;
};

#endif