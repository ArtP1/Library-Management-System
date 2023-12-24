#include <iostream>
#include <cassert>
#include <map>
#include <chrono>
#include "Book.h"
#include "Shelf.h"
#include "Reader.h"
#include "Library.h"
using namespace std;

Library& library = Library::getInstance();
void displayMainMenu();
void displayLibraryMenu();
void displayReaderMenu();
bool login(Reader& Reader);

int main() {
    int userChoice;

    do {
        displayMainMenu();
        std::cin >> userChoice;

        switch (userChoice) {
            case 1: 
                int libraryManagementChoice;

                // Library Management Menu
                do {
                    displayLibraryMenu();
                    std::cin >> libraryManagementChoice;

                    switch(libraryManagementChoice) {
                        case 1: {
                            // Create a Reader 
                            string name, phone;

                            cout << "Enter name: ";
                            std::cin.ignore();
                            getline(cin, name);


                            cout << "Enter phone number: ";
                            getline(cin, phone);

                            library.registerReader(Reader(name, phone));
                            cout << "Reader created successfully!" << endl;
                            break;
                        }
                        case 2:
                            // Add a Book
                            break;
                        case 3:
                            // Add a Shelf
                            break;
                        case 4:
                            // View Books
                            break;
                        case 5:
                            // View Shelves
                            library.listShelves();
                            break;
                        case 6:
                            // View Readers
                            library.listReaders();
                            break;
                        case 7:
                            // Available Books
                            break;
                        case 8:
                            // View Overdue Books
                            break;
                        case 9:
                            cout << "Exiting Library Mangement Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice! Please enter a valid option." << endl;
                            std::cin.clear();
                            std::cin.ignore();
                    }
                }while(libraryManagementChoice != 9);
                break;
            case 2: {
                // Reader Menu
                int cardNum;
                string phone;

                cout << "=== Welcome to the Library ===" << endl;
                cout << "Enter your card number: ";
                cin >> cardNum;

                cin.ignore();
                cout << "Enter your phone number: ";
                getline(cin, phone);

                if(library.hasReader(Reader(cardNum, phone))) {
                    int readerChoice;

                    do {
                        displayReaderMenu();
                        cin >> readerChoice;

                        switch(readerChoice) {
                            case 1:
                                // Check out a Book

                                break;
                            case 2:
                                // Return a Book
                                break;
                            case 3:
                                // View Borrowed Books
                                break;
                            case 4:
                                // View all books
                                library.listBooks();
                                break;
                            case 5:
                                cout << "Exiting Reader Menu..." << endl;
                                break;
                            default:
                                cout << "Invalid choice! Please enter a valid option." << endl;
                                std::cin.clear();
                                std::cin.ignore();
                        }
                    }while(readerChoice!= 5);
                } else {
                    cerr << "No reader found." << endl;
                }

                break;
            }
            case 3:   
                cout << "Exiting the program..." << endl;
                break;     
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
                std::cin.clear();
                std::cin.ignore();
        }
    }while(userChoice != 3);


    cout << "Have a Wonderful day!\nThanks for running Jaime's \"Library Management System\" Program" << endl << endl;
    return 0;
}

void displayMainMenu() {
    cout << "\n====== Main Menu ======\n"
         << "1. Manage the Library\n"
         << "2. Enter the Library as a Reader\n"
         << "3. Exit Program\n"
         << "=========================\n\n"
         << "Enter your choice: ";
}

void displayLibraryMenu() {
    cout << "\n====== Library Management System ======\n"
         << "1. Register a Reader\n"
         << "2. Register a Book\n"
         << "3. Add a Shelf\n"
         << "4. View Books\n"
         << "5. View Shelves\n"
         << "6. View Readers\n"
         << "7. Available Books\n"
         << "8. View Overdue Books\n"
         << "9. Exit\n"
         << "=======================================\n\n"
         << "Enter your choice: ";
}

void displayReaderMenu() {
    cout << "\n====== Reader Menu ======\n"
         << "1. Check out a Book\n"
         << "2. Return a Book\n"
         << "3. View Borrowed Books\n"
         << "4. View all books\n"
         << "5. Exit\n"
         << "=========================\n\n"
         << "Enter your choice: ";
}