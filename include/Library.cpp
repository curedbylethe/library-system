//
// Created by Parsa Jahanbani on 1/30/23.
//

#include "Library.h"
#include <iostream>
#include "Database.h"

using namespace std;
namespace library {

    void Library::start() const {
        cout << "Welcome to the Library";
        cout << "\n1. Login";
        cout << "\n2. Register";
        cout << "\n3. Exit";
        cout << "\nPlease enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Login";
                break;
            case 2:
                signUp();
                break;
            case 3:
                cout << "Exit";
                break;
            default:
                cout << "Invalid choice";
                break;
        }

    }

    void Library::signUp() const {
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
        cout << "\n3. Exit";
        cout << "\nPlease enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: {
                string role = "user";
                database::Database db;
                db.insertUser(username, firstName, lastName, password, birthdate, role);
                break;
            }
            case 2: {
                string role = "librarian";
                database::Database db;
                db.insertUser(username, firstName, lastName, password, birthdate, role);
                break;
            }
            case 3:
                start();
                break;
            default:
                cout << "Invalid choice";
                break;
        }
    }

    Library::Library() {
    }

    Library::~Library() {
    }
} // library