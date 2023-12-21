#ifndef READER_H
#define READER_H

#include <iostream>
#include <vector>
#include "Book.h"
using namespace std;

class Reader {
    public:
        // constructor(s)
        Reader();
        Reader(int card_num, string name, string phone);

        // setters & getters
        int getCardNum() const {return card_num;}
        string getName() const {return name;}
        string getPhone() const {return phone;}
        vector<Book> getBooks() const {return books;}
        int getMaxBookAmount() const {return max_books;}
        int getBookCount() const {return books.size();}
        void setCardNum(int new_card_num) {this->card_num = new_card_num;}
        void setName(string new_name) {this->name = new_name;}
        void setPhone(string new_phone) {this->phone = new_phone;}

        // other(s)
        void checkOutBook(Book& new_book);
        void returnBook(Book& target_book);
        bool hasBook(Book& target_book);
        
    private:
        int card_num;
        string name;
        string phone;
        vector<Book> books;
        const int max_books = 5;
};

#endif