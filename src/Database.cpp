//
// Created by Parsa Jahanbani on 1/28/23.
//
#include <iostream>
#include <vector>
#include "Library.h"

using namespace std;
namespace library {
    ofstream fileOut;

    void Database::insertUser(string &username, string &firstName, string &lastName,
                              string &password, string &birthdate, string &role) {
        fileOut.open("../data/users.txt", ios::out | ios::app);
        if (!fileOut.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }

        User user(username, password, firstName, lastName, birthdate);

        fileOut << user.getUuid() << ","
                << role << ","
                << username << ","
                << firstName << ","
                << lastName << ","
                << password << ","
                << birthdate << ","
                << "NULL" << endl;
        fileOut.close();
    }

    void Database::insertBook()  {
        fileOut.open("../data/books.txt", ios::out | ios::app);
        if (!fileOut.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }
        string title, edition, publisher, publishedYear, shelfNumber, isbn, length;
        vector<string> subjects, authors;
        cout << " ******* Add a Book *******" << endl;
        cout << "Enter Title: ";
        cin >> title;
        cout << "Enter Shelf Number: ";
        cin >> shelfNumber;
        cin.ignore();
        cout << "Enter Authors (separated by commas): ";
        string line;
        getline(cin, line);
        authors = Library::split(line, ',');
        cout << "Enter Edition: ";
        cin >> edition;
        cout << "Enter Publisher: ";
        cin >> publisher;
        cout << "Enter Published Year: ";
        cin >> publishedYear;
        cout << "Enter ISBN: ";
        cin >> isbn;
        cout << "Enter Length: ";
        cin >> length;
        cin.ignore();
        cout << "Enter Subjects: ";
        getline(cin, line);
        subjects = Library::split(line, ',');
        fileOut << title << ","
                << shelfNumber << ",";
        for (const auto &author : authors) {
            if (author != authors.back()) {
                fileOut << author << " ";
            } else {
                fileOut << author << ",";
            }
        }
        fileOut << edition << ","
                << publisher << ","
                << publishedYear << ","
                << isbn << ","
                << length << ",";
        for (const auto &subject : subjects) {
            if (subject != subjects.back()) {
                fileOut << subject << " ";
            } else {
                fileOut << subject << ",";
            }
        }
        fileOut << endl;
        fileOut.close();
    }

    Database::~Database() = default;

    Database::Database() = default;
} // database