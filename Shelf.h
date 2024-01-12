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
    bool hasBook(const Book& target_book) const {return books.find(target_book) != books.end();}
    void addBook(const Book& new_book);
    bool removeBook(const Book& target_book);
    void registerCheckedOutBook(const Book& target_book);
    void listShelfBooks();
    
    bool operator == (const Shelf& sh) const;
  private:
    int shelf_num;
    string subject;
    unordered_map<Book, int> books;
};

namespace std {
    template <>
    struct hash<Shelf> {
      size_t operator()(const Shelf& sh) const {
        return (hash<int>()(sh.getShelfNumber())) ^ (hash<string>()(sh.getSubject()) << 1);
      }
    };
}


#endif