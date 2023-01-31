//
// Created by Parsa Jahanbani on 1/30/23.
//

#include "Library.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
namespace library {

    void Library::start() {
        cout << "Welcome to the Library";
        cout << "\n1. Login";
        cout << "\n2. Register";
        cout << "\n3. Exit";
        cout << "\nPlease enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                Library::login();
                break;
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
        cout << "Welcome to the Library";
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
                break;
            }
            case 2:
                Book::borrowBook(user);
                break;
            case 3:
                cout << "Return";
                break;
            case 4:
                cout << "Exit";
                break;
            default:
                cout << "Invalid choice";
                student(user);
                break;
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

    void Library::login() {
        User user = User::login();
        user.getRole() == "user" ?
        Library::student(user) :
        Library::librarian();
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


    Library::Library() = default;

    Library::~Library() = default;

} // library