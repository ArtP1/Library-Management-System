#include <algorithm>
#include <sstream>
#include "Library.h"

// Retrieves a shelf based on a subject abbreviation.
// If the shelf exists, returns it; otherwise, displays an error message.
Shelf Library:: getShelf(const string shelf_subject_abbr) {
    auto iter = shelves.find(shelf_subject_abbr);

    if(iter != shelves.end()) {
        return iter->second;
    }

    cerr << "Error: No Shelf of subject \"" << shelf_subject_abbr << "\" exists" << endl << endl;
    return Shelf();
}

// Retrieves a reader based on a card number.
// If the reader exists, returns it; otherwise, displays an error message.
Reader Library:: getReader(const int card_num) {
    for(auto it = readers.begin(); it != readers.end(); it++) {
        if(it->getCardNum() == card_num) {
            return *it;
        }
    }

    cerr << "No Reader with Card (#" + to_string(card_num) + ") exists";
}

// Registers a new reader into the library's records.
// Checks for existing readers with the same card number or phone number.
void Library:: registerReader(const Reader& new_reader) {
    for(const Reader& existing_reader : readers) {
        if(existing_reader.getCardNum() == new_reader.getCardNum()) {
            cerr << "Warning: Reader with card (#" << new_reader.getCardNum() << ") already exists." << endl << endl;
            return;
        }

        if(existing_reader.getPhone() == new_reader.getPhone()) {
            cerr << "Warning: Reader with phone \"" << new_reader.getPhone() << "\" already exists." << endl << endl;
            return;
        }
    }

    readers.push_back(new_reader);
    cout << "Reader with card (#" << new_reader.getCardNum() << ") has been registered." << endl << endl;
}

// Removes a reader from the library's records.
// Searches for the reader by card number and removes if found; otherwise, displays an error.
void Library:: removeReader(const Reader& target_reader) {
    auto iter = find_if(readers.begin(), readers.end(), 
                [&target_reader](const Reader& r) { 
                    return r.getCardNum() == target_reader.getCardNum(); 
                });

    if (iter != readers.end()) {
        int removedReaderCardNum = iter->getCardNum();
        readers.erase(iter);
        cout << "Reader with card (#" << removedReaderCardNum << ") has been removed." << endl << endl;
    } else {
        cerr << "Error: Reader not found for removal." << endl << endl;
    }
}

// Updates an existing reader's information.
// Searches for the reader by card number and updates their details if found; otherwise, displays an error.
void Library:: updateReader(const Reader& target_reader, const Reader& updated_reader) {
    auto iter = find_if(readers.begin(), readers.end(),
                    [&target_reader](const Reader& r) {
                        return r.getCardNum() == target_reader.getCardNum();
                    });
    
    if(iter != readers.end()) {
        *iter = updated_reader;
    } else {
        cerr << "Error: Reader not found for updating." << endl << endl;
    }
}

// Adds a new shelf to the library's collection.
// Validates the shelf subject and generates an abbreviation before adding it to shelves.
void Library:: addShelf(const string shelf_subject) {
    if(shelf_subject.length() == 0) {
        cerr << "Error: Shelf subject cannot be empty." << endl << endl;
        return;
    } 

    for(char c : shelf_subject) {
        if(!isalpha(c) && c != ' ') {
            cerr << "Error: Shelf subject cannot contain non-alphabetical characters." << endl << endl;
            return;
        }
    }

    // Check if the shelf already exists by both abbreviation and subject
    string abbreviation = generateAbbreviation(shelf_subject);
    bool shelfExists = false;
    for (const auto& pair : shelves) {
        if (pair.first == abbreviation && pair.second.getSubject() == shelf_subject) {
            cerr << "Error: Shelf with subject \"" << shelf_subject << "\" already exists." << endl << endl;
            return;
        }
    }

    Shelf newShelf = Shelf(0, shelf_subject);
    shelves.emplace(abbreviation, newShelf);

    cout << "Shelf with subject \"" << shelf_subject << "\" has been added." << endl;
}

// void Library:: removeShelf(const string shelf_subject) {
//     auto iter = shelves.find()
// }

// Generates an abbreviation for a given subject to be used in shelf identification.
string Library:: generateAbbreviation(const string& subject) {
    stringstream ss(subject);
    string abbreviation = "";
    string word;

    while(ss >> word) {
        abbreviation += toupper(word[0]);
    }

    return abbreviation;
}
 
int Library:: generateUniqueCardNumber() {
    static int cardCounter = 1000;
    return cardCounter++;
}

// Lists all shelves present in the library.
void Library:: listShelves() {
    if(shelves.size() > 0) {
        cout << "All Shelves:" << endl;
        for(auto iter = shelves.begin(); iter!= shelves.end(); iter++) {
            cout << iter->first << " - \"" << iter->second.getSubject() << "\"" << endl;
        }
    } else {
        cerr << "No shelves present." << endl;
    }
}

// Lists all readers registered in the library.
void Library:: listReaders() {
    if(readers.size() > 0) {
        cout << "All Readers:" << endl;
        for(const Reader& reader: readers) {
            cout << "(" << reader.getCardNum() << ") - " << reader.getName() << endl;
        }
    } else {
        cerr << "No Readers have been registered." << endl;
    }
}

// Lists all books in the library.
void Library:: listBooks() {
    if(shelves.size() > 0) {
        for(auto iter = shelves.begin(); iter!= shelves.end(); iter++) {
            if(iter->second.getTotalBookCount() > 0) {
                iter->second.listShelfBooks();
            }
        }
    } else {
        cerr << "No shelves present." << endl;
    }
}


bool Library:: hasReader(const Reader& target_reader) {
    for(const Reader& reader: readers) {
        if(reader == target_reader) {
            return true;
        } 
    }
    return false;
}
// Clears all data in the library, including shelves and readers.
void Library::clearLibrary() {
    shelves.clear();
    readers.clear();
    cout << "The library's data has been wiped" << endl << endl;
}