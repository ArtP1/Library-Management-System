#include <algorithm>
#include <sstream>
#include "Library.h"

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

// Retrieves a shelf based on a subject abbreviation.
// If the shelf exists, returns it; otherwise, displays an error message.
Shelf Library:: getShelf(const string shelf_subject_abbr) {
    auto shelfIter = shelves.find(shelf_subject_abbr);

    if(shelfIter != shelves.end()) {
        return shelfIter->second;
    }

    cerr << "Error: No Shelf of subject \"" << shelf_subject_abbr << "\" exists" << endl << endl;
    return Shelf();
}

// Removes a shelf based on a subject abbreviation.
void Library:: removeShelf(const string shelf_subject_abbr, const Shelf& shelf) {
    auto shelfRange = shelves.equal_range(shelf_subject_abbr);

    for (auto shelfIter = shelfRange.first; shelfIter != shelfRange.second; ++shelfIter) {
        if (shelfIter->second == shelf) {
            shelves.erase(shelfIter);
            cout << "Shelf with subject \"" << shelf_subject_abbr << "\" has been removed." << endl;
            return;
        }
    }

    cerr << "Error: No matching Shelf found for removal with subject \"" << shelf_subject_abbr << "\"." << endl << endl;
}

// Updates a shelf based on a subject abbreviation.
void Library::updateShelf(const Shelf& target_shelf, const Shelf& updated_shelf) {
    auto shelfRange = shelves.equal_range(target_shelf.getSubject());

    // Find the specific shelf to update within the range
    auto shelfIter = find_if(shelfRange.first, shelfRange.second,
                             [&target_shelf](const pair<const string, Shelf>& shelfPair) {
                                 return shelfPair.second == target_shelf;
                             });

    if (shelfIter != shelfRange.second) {
        shelves.erase(shelfIter);

        // Insert the updated shelf with the new key
        string abbreviation = generateAbbreviation(updated_shelf.getSubject());
        shelves.insert({abbreviation, updated_shelf});
    } else {
        cerr << "Error: Shelf not found for updating." << endl << endl;
    }
}

// Lists all shelves present in the library.
void Library:: listShelves() {
    if(!shelves.empty()) {
        cout << "All Shelves:" << endl;
        for(auto iter = shelves.begin(); iter != shelves.end(); iter++) {
            cout << iter->first << " - \"" << iter->second.getSubject() << "\"" << endl;
        }
    } else {
        cerr << "No shelves present." << endl;
    }
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
    return Reader();
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
    auto readerIter = find_if(readers.begin(), readers.end(), 
                [&target_reader](const Reader& r) { 
                    return r.getCardNum() == target_reader.getCardNum(); 
                });

    if (readerIter != readers.end()) {
        int removedReaderCardNum = readerIter->getCardNum();
        readers.erase(readerIter);
        cout << "Reader with card (#" << removedReaderCardNum << ") has been removed." << endl << endl;
    } else {
        cerr << "Error: Reader not found for removal." << endl << endl;
    }
}

// Updates an existing reader's information.
// Searches for the reader by card number and updates their details if found; otherwise, displays an error.
void Library:: updateReader(const Reader& target_reader, const Reader& updated_reader) {
    auto readerIter = find_if(readers.begin(), readers.end(),
                    [&target_reader](const Reader& r) {
                        return r.getCardNum() == target_reader.getCardNum();
                    });
    
    if(readerIter != readers.end()) {
        *readerIter = updated_reader;
    } else {
        cerr << "Error: Reader not found for updating." << endl << endl;
    }
}

// Lists all readers registered in the library.
void Library:: listReaders() {
    if(!readers.empty()) {
        cout << "All Readers:" << endl;
        for(const Reader& reader: readers) {
            cout << "(" << reader.getCardNum() << ") - " << reader.getName() << endl;
        }
    } else {
        cerr << "No Readers have been registered." << endl;
    }
}

// Checks if the library contains a reader with a given card number.
bool Library:: hasReader(const Reader& target_reader) {
    return find(readers.begin(), readers.end(), target_reader) != readers.end();
}

// Adds a new book to the library's collection.
// If there are multiple shelfs with the same subject abbreviation, gives the user the option to choose from all matching shelfs by shelf number.
void Library:: addBook(const Book& new_book, string shelf_subject_abbr) { 
    if (!shelves.empty()) {
        auto shelfRange = shelves.equal_range(shelf_subject_abbr);

        if(shelfRange.first != shelfRange.second) {
            if(next(shelfRange.first) == shelfRange.second) { // If there is only one shelf with the abbreviation
                auto selectedShelfIter = shelfRange.first;
                selectedShelfIter->second.addBook(new_book);
                cout << "Book added to shelf with subject \"" << selectedShelfIter->second.getSubject() << "\"." << endl;
                return;
            }

            do {
                cout << "Shelves with subject abbreviation \"" << shelf_subject_abbr << "\":" << endl;
                for (auto shelfIter = shelfRange.first; shelfIter != shelfRange.second; shelfIter++) {
                    cout << "(#" << shelfIter->second.getShelfNumber() << ") "<< shelfIter->first << " - " << shelfIter->second.getSubject() << endl;
                }
                

                // Ask the user to choose a specific shelf subject
                cout << "Enter the Shelf Number where you want to add the book: ";
                int selectedShelfNumber;
                cin >> selectedShelfNumber;
                
                auto selectedShelfIter = find_if(shelfRange.first, shelfRange.second, [selectedShelfNumber](const auto& pair) {
                    return pair.second.getShelfNumber() == selectedShelfNumber;
                });

                if(selectedShelfIter != shelfRange.second) {
                    selectedShelfIter->second.addBook(new_book);
                    cout << "Book added to shelf with subject \"" << selectedShelfIter->second.getSubject() << "\"." << endl;
                    break;
                } else {
                    cerr << "Error: Invalid Shelf Number." << endl << endl;
                }
            } while(true);

        } else {
            cerr << "Error: No Shelf with subject abbreviation \"" << shelf_subject_abbr << "\" exists." << endl << endl;
        }
    } else {
        cerr << "Error: No shelves present." << endl;
    }
}

// Removes a book from the library's collection.
void Library:: removeBook(const Book& target_book, string shelf_subject_abbr) {
    if (!shelves.empty()) {
        auto shelfRange = shelves.equal_range(shelf_subject_abbr);

        for (auto shelfIter = shelfRange.first; shelfIter != shelfRange.second; shelfIter++) {
            if (shelfIter->second.hasBook(target_book)) {
                shelfIter->second.removeBook(target_book);
                cout << "Book removed from shelf with subject \"" << shelfIter->second.getSubject() << "\"." << endl;
                return;  // Remove the book from the first matching shelf and exit the loop
            }
        }

        cerr << "Error: No matching book found on shelf with subject abbreviation \"" << shelf_subject_abbr << "\"." << endl << endl;
    } else {
        cerr << "Error: No shelves present." << endl;
    }
}

// Lists all books in the library.
void Library:: listBooks() {
    if(!shelves.empty()) {
        for(auto shelfIter = shelves.begin(); shelfIter != shelves.end(); shelfIter++) {
            if(shelfIter->second.getTotalBookCount() > 0) {
                shelfIter->second.listShelfBooks();
            }
        }
    } else {
        cerr << "No shelves present." << endl;
    }
}

// Clears all data in the library, including shelves and readers.
void Library:: clearLibrary() {
    shelves.clear();
    readers.clear();
    cout << "The library's data has been wiped" << endl << endl;
}

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

// Generates a unique card number for a new reader.
int Library:: generateUniqueCardNumber() {
    static int cardCounter = 1000;
    return cardCounter++;
}
