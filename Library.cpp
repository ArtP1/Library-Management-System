#include "Library.h"

Shelf Library:: getShelf(const string& shelf_subject) {
    try{
        auto iter = shelves.find(shelf_subject);

        if(iter == shelves.end()) {
            throw runtime_error("Error: No Shelf of subject \"" + shelf_subject + "\" exists" );
        }
        
        return iter->second;
    } catch(const char* errMsg) {
        cerr << errMsg << endl;
        return Shelf();
    }
}

Reader Library:: getReader(const int& card_num) {
    try {
        for(auto it = readers.begin(); it != readers.end(); it++) {
            if()
        }
    }
}