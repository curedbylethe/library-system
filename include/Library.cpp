//
// Created by Parsa Jahanbani on 1/30/23.
//

#include "Library.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;
namespace library {

    void Library::login() {
        User user = User::login();
        user.getRole() == "user" ?
        Library::student(user) :
        Library::librarian();
    }

    void Library::returnBook(User &user) {
        if (user.getBorrowed().empty()) {
            cout << "You have not borrowed any books";
            student(user);
        }
        cout << "Here's the list of books you have borrowed: ";
        for (auto &book: user.getBorrowed()) {
            cout << book << endl;
        }
        cin.ignore();
        cout << "Enter the book ID you wish to return"
                "\nYou can enter multiple book IDs separated by a comma:";
        string bookUuid;
        getline(cin, bookUuid);
        vector<string> bookUuids = Library::split(bookUuid, ',');
        for (auto &book: bookUuids) {
            user.returnBook(book);
        }
        student(user);
    }

    void Library::searchForBooks(User &user) {
        auto books = Book::searchBook();
        cout << "Books found: " << books.size() << endl;
        for (auto &[title, book] : books) {
            cout << book << endl;
        }
        cout << "Do you want to borrow a book? (y/n): ";
        char y_or_n;
        cin >> y_or_n;
        if (y_or_n == 'y') {
            Book::borrowBook(user, &books);
        } else {
            student(user);
        }
    }

    void Library::borrow(User &user) {
        if (user.getBorrowed().size() >= 2) {
            cout << "You have reached the maximum number of books you can borrow";
            student(user);
        }
        Book::borrowBook(user);
        if (user.getBorrowed().size() < 2) {
            cout << "Do you want to borrow another book? (y/n): ";
            char y_or_n;
            cin >> y_or_n;
            if (y_or_n == 'y') {
                borrow(user);
            } else {
                cout << "Do you wish to return a book? (y/n): ";
                cin >> y_or_n;
                if (y_or_n == 'y') {
                    Library::returnBook(user);
                } else {
                    student(user);
                }
            }
        } else {
            cout << "You can borrow any more books."
                    "\nExit the program by entering e or go back to the main menu by entering m: " << endl;
            char e_or_m;
            cin >> e_or_m;
            if (e_or_m == 'e') {
                exit(0);
            } else if (e_or_m == 'm') {
                student(user);
            } else {
                cout << "Invalid choice";
                student(user);
            }
        }
    }

    /* UI */

    void Library::start() {
        cout << "\nWelcome to the Library";
        cout << "\n1. Login";
        cout << "\n2. Register";
        cout << "\n3. Exit";
        cout << "\nPlease enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                Library::login();
            }
            case 2:
                signUp();
                break;
            case 3:
                cout << "Exit";
                break;
            default:
                cout << "Invalid choice\n";
                start();
                break;
        }
    }

    void Library::student(User &user) {
        cout << "\nWelcome to the Library";
        cout << "\n1. Search";
        cout << "\n2. Borrow";
        cout << "\n3. Return";
        cout << "\n4. Exit";
        cout << "\nPlease enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                Library::searchForBooks(user);
            }
            case 2:
                Library::borrow(user);
            case 3: {
                Library::returnBook(user);
            }
            case 4:
                cout << "Exit";
                break;
            default:
                cout << "Invalid choice";
                student(user);
        }
    }

    void Library::librarian() {
        cout << "Welcome to the Library";
        cout << "\n1. Add Book";
        cout << "\n2. Remove Book";
        cout << "\n3. Add User";
        cout << "\n4. Remove User";
        cout << "\n5. Exit";
        cout << "\nPlease enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Add Book";
                break;
            case 2:
                cout << "Remove Book";
                break;
            case 3:
                cout << "Add User";
                break;
            case 4:
                cout << "Remove User";
                break;
            case 5:
                cout << "Exit";
                break;
            default:
                cout << "Invalid choice";
                librarian();
                break;
        }
    }

    void Library::signUp() {
        string username, firstName, lastName, password, birthdate;
        cout << " ******* Add User *******";
        cout << "\nEnter Username: ";
        cin >> username;
        cout << "\nEnter Your Name ";
        cin >> firstName >> lastName;
        cout << "\nEnter Password: ";
        cin >> password;
        cout << "\nEnter Birthdate: ";
        cin >> birthdate;

        cout << "Select a role: ";
        cout << "\n1. User";
        cout << "\n2. Librarian";
        cout << "\n3. Go back";
        cout << "\n4. Exit";
        cout << "\nPlease enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                string role = "user";
                Database::insertUser(username, firstName, lastName, password, birthdate, role);
                break;
            }
            case 2: {
                string role = "librarian";
                Database::insertUser(username, firstName, lastName, password, birthdate, role);
                break;
            }
            case 3:
                start();
                break;
            case 4:
                cout << "Exit";
                break;
            default:
                cout << "Invalid choice";
                signUp();
                break;
        }
    }

    /* Helpers */

    vector<string> Library::split(const string &str, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream tokenStream(str);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    string Library::join(vector<string> v, char delimiter) {
            string result = "";
            for (int i = 0; i < v.size(); i++) {
                result += v[i];
                if (i < v.size() - 1) {
                    result += delimiter;
                }
            }
            return result;
    }

    string Library::trim(string &s) {
        s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
            return !isspace(ch);
        }));
        s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
            return !isspace(ch);
        }).base(), s.end());
        return s;

    }

    Library::Library() = default;

    Library::~Library() = default;

} // library