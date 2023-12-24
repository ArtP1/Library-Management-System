#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <vector>
#include <map>
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

        // getters & setters
        Shelf getShelf(const string shelf_subject_abbr);
        int getShelfCount() const {return shelves.size();}
        Reader getReader(const int card_num);
        int getReaderCount() const {return readers.size();}
        vector<Reader> getReaders() const {return readers;}
        multimap<string, Shelf> getShelves() const {return shelves;}

        // other(s)
        void registerReader(const Reader& new_reader);
        void removeReader(const Reader& target_reader);
        void updateReader(const Reader& target_reader, const Reader& updated_reader);
        void addShelf(const string shelf_subject);
        void removeShelf(const string shelf_subject);
        void clearLibrary();

        void listShelves();
        void listReaders();
        void listBooks();
        bool hasReader(const Reader& target_reader);

    private:
        multimap<string, Shelf> shelves;
        vector<Reader> readers;
        string generateAbbreviation(const string& subject);
        int generateUniqueCardNumber();
    protected:
        Library() = default;
};

#endif