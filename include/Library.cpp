//
// Created by Parsa Jahanbani on 1/30/23.
//

#include "Library.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
namespace library {

    void Library::login() {
        User user = User::login();
        user.getRole() == "user" ?
        Library::student(user) :
        Library::librarian(user);
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

    void Library::addNewBook() {
        string title, shelfNum, authorsStr, edition, publisher, publishedYear, isbn, length, subjectsStr ;
        cout << " ******* Add A New Book *******\n";
        cout << "Enter Title: ";
        cin >> title;
        cin.ignore();
        cout << "Enter Shelf Number ";
        cin >> shelfNum;
        cin.ignore();
        cout << "Enter Authors (separate by commas if more than one): ";
        getline(cin, authorsStr);
        cin.ignore();
        vector<string> authors = Library::split(authorsStr, ',');
        for (auto &author: authors) {
            author = Library::trim(author);
        }
        cout << "Enter Edition: ";
        cin >> edition;
        cin.ignore();
        cout << "Enter Publisher: ";
        cin >> publisher;
        cin.ignore();
        cout << "Enter Published Year: ";
        cin >> publishedYear;
        cout << "Enter ISBN: ";
        cin >> isbn;
        cout << "Enter Length: ";
        cin >> length;
        cin.ignore();
        cout << "Enter Subjects (separate by commas if more than one): ";
        getline(cin, subjectsStr);
        vector<string> subjects = Library::split(subjectsStr, ',');
        for (auto &subject: subjects) {
            subject = Library::trim(subject);
        }
        Book book = Book(title, shelfNum, authors, isbn, edition,
                         publisher, subjects, length, publishedYear);
        Database::insertBook(book);
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
                exit(0);
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
        cout << "\n4. Log out";
        cout << "\n5. Exit";
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
                Library::start();
            case 5:
                exit(0);
            default:
                cout << "Invalid choice";
                student(user);
        }
    }

    void Library::librarian(User &user) {
        cout << "Welcome to the Library";
        cout << "\n1. Add Book";
        cout << "\n2. Remove Book";
        cout << "\n3. Add User";
        cout << "\n4. Remove User";
        cout << "\n5. Log out";
        cout << "\n6. Exit";
        cout << "\nPlease enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                Library::addNewBook();
                Library::librarian(user);
            case 2:
                Library::removeBook();
                Library::librarian(user);
            case 3:
                Library::addUser(user);
            case 4:
                Library::removeUser();
                Library::librarian(user);
            case 5:
                Library::start();
            case 6:
                exit(0);
            default:
                cout << "Invalid choice";
                librarian(user);
        }
    }

    void Library::signUp() {
        string username, firstName, lastName, password, birthdate;
        cout << " ******* Add User *******";
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Your Full Name ";
        cin >> firstName >> lastName;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Birthdate: ";
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
                User user(username, firstName, lastName, password, birthdate, role);
                Database::insertUser(user);
                student(user);
            }
            case 2: {
                string role = "librarian";
                User user(username, firstName, lastName, password, birthdate, role);
                Database::insertUser(user);
                librarian(user);
            }
            case 3:
                start();
            case 4:
                exit(0);
            default:
                cout << "Invalid choice";
                signUp();
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

    void Library::removeBook() {
        cout << "Enter the title or ID Number of the book you want to remove: ";
        string titleOrId;
        cin >> titleOrId;
        Database::deleteLine("books", titleOrId);
    }

    void Library::removeUser() {
        cout << "Enter the ID or Username of the user you want to remove: ";
        string titleOrId;
        cin >> titleOrId;
        Database::deleteLine("users", titleOrId);
    }

    void Library::addUser(User &admin) {
        string username, firstName, lastName, password, birthdate;
        cout << " ******* Add User *******";
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Your Full Name ";
        cin >> firstName >> lastName;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Birthdate: ";
        cin >> birthdate;
        cout << "Select a role: ";
        cout << "\n1. User";
        cout << "\n2. Librarian";
        cout << "\nPlease enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                string role = "user";
                User user(username, password, firstName, lastName, birthdate, role);
                Database::insertUser(user);
                librarian(admin);
            }
            case 2: {
                string role = "librarian";
                User user(username, password, firstName, lastName, birthdate, role);
                Database::insertUser(user);
                librarian(admin);
            }
            default:
                cout << "Invalid choice";
                librarian(admin);
        }
    }

    Library::Library() = default;

    Library::~Library() = default;

} // library