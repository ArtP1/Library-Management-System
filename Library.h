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
        multimap<string, Shelf> getShelves() const {return shelves;}

        Reader getReader(const int card_num);
        int getReaderCount() const {return readers.size();}
        vector<Reader> getReaders() const {return readers;}

        // other(s)
        bool hasReader(const Reader& target_reader);
        void registerReader(const Reader& new_reader);
        void removeReader(const Reader& target_reader);
        void updateReader(const Reader& target_reader, const Reader& updated_reader);
        void listReaders();

        void addShelf(const string shelf_subject);
        void removeShelf(const string shelf_subject_abbr, const Shelf& shelf) ;
        void updateShelf(const Shelf& target_shelf, const Shelf& updated_shelf);
        void listShelves();

        void addBook(const Book& new_book, string shelf_subject_abbr);
        void removeBook(const Book& target_book, string shelf_subject_abbr); 
        void updateBook(const Book& target_book, const Book& updated_book); // NEW
        void listBooks();
        void listOverdueBooks(); // NEW
        void clearLibrary();
    private:
        multimap<string, Shelf> shelves;
        vector<Reader> readers;
        string generateAbbreviation(const string& subject);
        int generateUniqueCardNumber();
    protected:
        Library() = default;
};

#endif