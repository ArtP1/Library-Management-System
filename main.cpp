#include <iostream>
#include <cassert>
#include <map>
#include <chrono>
#include "Book.h"
#include "Shelf.h"
#include "Reader.h"
#include "Library.h"
using namespace std;

Library &library = Library::getInstance();
void displayMainMenu();
void displayLibraryMenu();
void displayReaderMenu();
bool login(Reader &Reader);
void displayShelfManagementMenu();
void displayBookManagementMenu();
void displayReaderManagementMenu();

int main()
{
    int userChoice;

    do {
        // Main Menu 
        displayMainMenu();
        cin >> userChoice;

        switch (userChoice) {
            // Library Management Menu 
            case 1: {
                int libraryManagementChoice;

                do {
                    displayLibraryMenu();
                    cin >> libraryManagementChoice;

                    switch (libraryManagementChoice) {
                        // Reader Management Menu
                        case 1: {
                            int readerManagementChoice;
                            
                            do {
                                displayReaderManagementMenu();
                                cin >> readerManagementChoice;

                                switch(readerManagementChoice) {
                                    // Register a Reader
                                    case 1:
                                        break;

                                    // Remove Reader
                                    case 2:
                                        break;

                                    // Update Reader Information
                                    case 3:
                                        break;

                                    // View Readers
                                    case 4:
                                        break;
                                        
                                    // Back to Library Management Menu
                                    case 5:
                                        cout << "Exiting Library Mangement Menu..." << endl;
                                        break;
                                    default:
                                        break;
                                } 
                            } while(readerManagementChoice != 5);
                            
                            break;
                        }
                        // Book Management Menu
                        case 2: {
                            int bookManagementChoice;
                            
                            do {
                                displayBookManagementMenu();
                                cin >> bookManagementChoice;

                                switch(bookManagementChoice) {
                                    // Register a Book
                                    case 1:

                                        break;

                                    // Remove Book
                                    case 2:
                                        

                                        break;

                                    // Update Book Information
                                    case 3:
                                        

                                        break;

                                    // View Books
                                    case 4:
                                        

                                        break;

                                    // Back to Library Management Menu
                                    case 5:
                                        cout << "Exiting Library Mangement Menu..." << endl;
                                        break;
                                    default:
                                        break;
                                } 
                            } while(bookManagementChoice!= 5);
                            
                            break;
                        }
                        // Shelf Management Menu
                        case 3: {
                            int shelfManagementChoice;

                            do {
                                displayShelfManagementMenu();
                                cin >> shelfManagementChoice;

                                switch(shelfManagementChoice) {
                                    // Add a Shelf
                                    case 1:

                                        break;
                                        
                                    // Remove a Shelf
                                    case 2:

                                        break;

                                    // Update Shelf Information
                                    case 3:
                                    

                                        break;

                                    // View Shelves
                                    case 4:

                                        break;

                                    // Back to Library Management Menu
                                    case 5:
                                        cout << "Exiting Library Mangement Menu..." << endl;
                                        break;
                                    default:
                                        break;
                                }
                            } while(shelfManagementChoice!= 5);
                            
                            break;

                        }
                        // View Available Books
                        case 4: 
                            library.listBooks();
                            break;

                        // View Overdue Books
                        case 5: 

                            break;

                        // Back to Main Menu
                        case 6:
                            cout << "Exiting Library Mangement Menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice! Please enter a valid option." << endl;
                            cin.clear();
                            cin.ignore();
                    }
                } while (libraryManagementChoice != 9);
                break;
            }
            // Reader Menu
            case 2: {
                int cardNum;
                string phone;

                cout << "=== Welcome to the Library ===" << endl;
                cout << "Enter your card number: ";
                cin >> cardNum;

                cin.ignore();
                cout << "Enter your phone number: ";
                getline(cin, phone);

                if (library.hasReader(Reader(cardNum, phone))) {
                    int readerChoice;

                    do {
                        displayReaderMenu();
                        cin >> readerChoice;

                        switch (readerChoice) {
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
                                cin.clear();
                                cin.ignore();
                        }
                    } while (readerChoice != 5);
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
                cin.clear();
                cin.ignore();
        }
    } while (userChoice != 3);

    cout << "Have a Wonderful day!\nThanks for running Jaime's \"Library Management System\" Program" << endl
         << endl;
    return 0;
}

void displayMainMenu()
{
    cout << "\n====== Main Menu ======\n"
         << "1. Manage library\n"
         << "2. Enter library as a Reader\n"
         << "3. Exit Program\n"
         << "=========================\n\n"
         << "Enter your choice: ";
}

void displayLibraryMenu()
{
    cout << "\n====== Library Management System ======\n"
         << "1. Reader Management\n"
         << "2. Book Management\n"
         << "3. Shelf Management\n"
         << "4. View Available Books\n"
         << "5. View Overdue Books\n"
         << "6. Exit\n"
         << "=======================================\n\n"
         << "Enter your choice: ";
}

void displayReaderMenu()
{
    cout << "\n====== Reader Menu ======\n"
         << "1. Check out a Book\n"
         << "2. Return a Book\n"
         << "3. View Borrowed Books\n"
         << "4. View all books\n"
         << "5. Exit\n"
         << "=========================\n\n"
         << "Enter your choice: ";
}

void displayReaderManagementMenu() {
    cout << "\n====== Reader Management ======\n"
         << "1. Register a Reader\n"
         << "2. Remove a Reader\n"
         << "3. Update Reader Information\n"
         << "4. View Readers\n"
         << "5. Back to Main Menu\n"
         << "==============================\n\n"
         << "Enter your choice: ";
}

void displayBookManagementMenu() {
    cout << "\n====== Book Management ======\n"
         << "1. Register a Book\n"
         << "2. Remove a Book\n"
         << "3. Update Book Information\n"
         << "4. View Books\n"
         << "5. Back to Main Menu\n"
         << "=============================\n\n"
         << "Enter your choice: ";
}

void displayShelfManagementMenu() {
    cout << "\n====== Shelf Management ======\n"
         << "1. Add a Shelf\n"
         << "2. Remove a Shelf\n"
         << "3. View Shelves\n"
         << "4. Back to Main Menu\n"
         << "==============================\n\n"
         << "Enter your choice: ";
}
