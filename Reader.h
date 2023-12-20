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
        int getBookCount() const {return books.size();}
        void setCardNum(int new_card_num);
        void setName(string new_name);
        void setPhone(string phone);
        
        // other(s)
        void addBook(Book new_book);
        void removeBook(Book target_book);
        bool hasBook(Book target_book);
        
    private:
        int card_num;
        string name;
        string phone;
        vector<Book> books;
};

#endif