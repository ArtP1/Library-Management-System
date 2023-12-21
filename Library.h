#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include "Book.h"
#include "Reader.h"
#include "Shelf.h"
using namespace std;

class Library {
    public:
        static Library& getInstance() {
            static Library instance;
            return instance;
        }

        Shelf getShelf(const string& shelf_subject);
        Reader getReader(const int& card_num);
        Reader getReader(const int& card_num);
    private:
        unordered_map<string, Shelf> shelves;
        vector<Reader> readers;
    protected:
        Library() = default;
};

#endif