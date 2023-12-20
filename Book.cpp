#include "Book.h"
#include <cassert>
#include <string>

Book:: Book(string title, string author, int year_published, string isbn, string genre) {
  setTitle(title);
  setAuthor(author);
  setYearPublished(year_published);
  setIsbn(isbn);
  setGenre(genre);
  setAvailability(false);
}

// function to set & validate the title of a book 
bool Book:: setAuthor(string new_author) {
  try {
    for(char c : new_author) {
      if(!isalpha(c) && c != ' ') {
          throw "Error: Invalid Author - Should only contain alphabetical characters";
      }
    }
    
    this->author = new_author;
    return true;
  } catch(const char* errMsg) {
    cout << errMsg << endl;
    return false;
  }
}

// function to set & validate the ISBN of a book
bool Book:: setIsbn(string new_isbn) {
  try {
    if(new_isbn.length() != 17) {
      throw "Error: Invalid ISBN Length - Should be 13 characters in this format (978-X-XXX-XXXXX-N)";
    }


    // Retrieves the Book's first 3 characters which should be "978"
    string isbn_identifier = new_isbn.substr(0, 3);

    // Retrieves the Book's Country or Language Group identifier which should be either 1 or 0
    string isbn_country_lan_identifier = new_isbn.substr(4, 1);

    // Retrieves the Book's Isbn Publisher number
    string isbn_publisher_identifier = new_isbn.substr(6, 3);

    // Retrieves the Book's Title/Edition identifier
    string isbn_book_title_edition_idenfitier = new_isbn.substr(10, 5);

    // Retrieves the Book's Check digit
    string isbn_check_digit = new_isbn.substr(15, 1);
    
    if(isbn_identifier != "978") {
      throw "Error: Invalid ISBN Identifier";
    }

    if(isbn_country_lan_identifier != "1" && isbn_country_lan_identifier != "0") {
      throw "Error: Invalid ISBN Country or Language Identifier - Should be (1 or 0)";
    }

    if(isbn_publisher_identifier.length() != 3) {
      throw "Error: Invalid ISBN Publisher Identifer - Should be 3 characters";
    }

    if(isbn_book_title_edition_idenfitier.length() != 5) {
      throw "Error: Invalid ISBN Book Title/Edition Identifier - Should be 5 characters";
    }

    if((isbn_check_digit[0] < '0' && isbn_check_digit[0] > '9') && isbn_check_digit != "X") {
      throw "Error: Invalid ISBN Check Digit - Should be any number from (0-9) or X (10)";
    }

    this->isbn = new_isbn;
    return true;
    
  } catch(const char* errMsg) {
    cout << errMsg << endl;
    return false;
  }
}

// funciton to set & validate the year publishing of a book
bool Book:: setYearPublished(int year_published) {
  try {
    if(year_published < 1455 || year_published > 2023) {
      throw "Error: Invalid Book Publishing Year - Should be a publishing year from 1455-2023";
    }

    this->year_published = year_published;
    return true;
    
  } catch(const char* errMsg) {
    cout << errMsg << endl;
    return false;
  }
}


bool Book::operator == (const Book& b) const {
  return this->title == b.getTitle() && this->author == b.getAuthor() && this->year_published == b.getYearPublished() && this->isbn == b.getIsbn() && this->genre == b.getGenre();
}