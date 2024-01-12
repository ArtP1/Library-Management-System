#include "Reader.h"
#include <algorithm>

Reader:: Reader() {

}
Reader:: Reader(string name, string phone) {
    this->card_num = generateUniqueCardNumber();
    setName(name);
    setPhone(phone);
}

Reader:: Reader(int card_num, string phone) {
    setCardNum(card_num);
    setPhone(phone);
}

void Reader:: checkOutBook(Book& new_book) {
    int numBooksCheckedOut = books.size();
    if(numBooksCheckedOut == max_books) {
        cout << "You must return 1 of " << numBooksCheckedOut << " books that you currently have" << endl;
    } else {
        cout << "Checked out new book" << endl;
        books.push_back(new_book);
        if(books.size() > 1) {
            cout << "You currently have " << books.size() << " books checked out" << endl << endl;
        } else {
            cout << "You currently have " << books.size() << " book checked out" << endl << endl;
        }
    }
}

void Reader:: returnBook(Book& target_book) {
    
    auto iter = remove(books.begin(), books.end(), target_book);

    if(iter == books.end()) {
        cout << "Reader doesn't have this \"" << target_book.getTitle() << "\" book (" << target_book.getIsbn() << ")" << endl << endl;
    } else {
        books.erase(iter, books.end());        
        cout << "Book \"" << target_book.getTitle() << "\" (" << target_book.getIsbn() << ") was returned from Reader #" << card_num << endl << endl;
    }
}

bool Reader:: hasBook(Book& target_book) {
    auto iter = find(books.begin(), books.end(), target_book);

    if(iter != books.end()) {
        cout << "Reader has book \"" << target_book.getTitle() << "\" (" << target_book.getIsbn() << ")"<< endl << endl;
        return true;
    } else {
        cout << "Reader doesn't have book \"" << target_book.getTitle() << "\" (" << target_book.getIsbn() << ")"<< endl << endl; 
    }

    return false;
}

int Reader:: generateUniqueCardNumber() {
    static int nextCardNumber = 1000; 
    return ++nextCardNumber; 
}

bool Reader:: operator == (const Reader& other) const {
    return this->card_num == other.getCardNum() && this->phone == other.getPhone();
}
