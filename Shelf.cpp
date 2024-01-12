#include "Shelf.h"
Shelf:: Shelf() {

}

Shelf:: Shelf(int shelf_num, string subject) {
  setShelfNumber(shelf_num);
  setSubject(subject);
  cout << "A new " << subject << " shelf was added." << endl << endl;
}

// function that outputs the book count of a specific book within a shelf
int Shelf:: getBookCount(const Book& target_book) {
  auto it = books.find(target_book);

  if(it != books.end()) {
    return it->second;
  } else {
    return -1;
  }
}

// function that adds a book to a shelf
void Shelf:: addBook(const Book &new_book) {
  int book_count = getBookCount(new_book);

  if(book_count > 0) {
    books[new_book] = book_count + 1;
    cout << "Added a copy of the book to the shelf." << endl << endl;
  } else {
    cout << "Added a new book to the shelf." << endl << endl;
    books.insert(pair<Book, int>(new_book, 1));
  }
}

// function that removes a book from a shelf
bool Shelf:: removeBook(const Book& target_book) {
  int book_count = getBookCount(target_book);

  if(book_count >= 1) {
    books[target_book] = book_count - 1;
    cout << "Successfully removed a copy of \"" << target_book.getTitle() <<  "\" from the shelf." << endl << endl;
    return true;
  }

  books.erase(target_book);
  cout << "Book removed from the shelf." << endl << endl;
  return false;
}

void Shelf:: registerCheckedOutBook(const Book& target_book) {
  int book_count = getBookCount(target_book);

  if(book_count >= 1) {
    books[target_book] = book_count - 1;
    cout << "Successfully registered checked out book!" << endl << endl;
  } else {
    cerr << "Book is not available." << endl << endl;
  }
}



// function that outputs the shelf within a shelf
void Shelf:: listShelfBooks() {
  if(!books.empty()) {
    cout << "Books from the \"" << subject << "\" shelf include: \n";
    for(const auto& pair : books) {
      const Book& book = pair.first;
      int count = pair.second;

      book.printBook();
    }
  }
}

bool Shelf:: operator == (const Shelf& sh) const {
  return this->shelf_num == sh.getShelfNumber() && this->subject == sh.getSubject();
}
