#ifndef BOOK_H
#define BOOK_H

#include <iostream>
using namespace std;

class Book {
  public:
    // constructor(s)
    Book();
    Book(string title, string author, int year_published, string isbn, string genre);

    // getters & setters
    string getTitle() const {return title;}
    string getAuthor() const {return author;}
    int getYearPublished() const {return year_published;}
    string getIsbn() const {return isbn;}
    string getGenre() const {return genre;}
    bool getAvailability() const {return available;}
    void setTitle(string new_title) {this->title = new_title;}
    bool setAuthor(string new_author);
    bool setYearPublished(int year_published);
    bool setIsbn(string new_isbn);
    void setGenre(string new_genre) {this->genre = new_genre;}
    void setAvailability(bool isAvailable) {this->available = isAvailable;}

    // other(s)
    void returnBook();
    void borrowBook();
    
    bool operator == (const Book& b) const;
  private:
    string title;
    string author;
    int year_published;
    string isbn;
    string genre;
    bool available;
};

namespace std {
    template <>
    struct hash<Book> {
      size_t operator()(const Book& b) const {
        return (hash<string>()(b.getTitle())) ^ (hash<string>()(b.getAuthor()) << 1) ^ (hash<int>()(b.getYearPublished()) << 2) ^ (hash<string>()(b.getIsbn()) << 3) ^ (hash<string>()(b.getGenre()) << 4);
      }
    };
}

#endif 