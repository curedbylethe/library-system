//
// Created by Parsa Jahanbani on 1/28/23.
//
#include <iostream>
#include <fstream>
#include <string>
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
                << endl;
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
        size_t start = 0;
        size_t end = line.find(",");
        while (end != string::npos) {
            authors.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(",", start);
        }
        authors.push_back(line.substr(start, end));
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
        start = 0;
        end = line.find(",");
        while (end != string::npos) {
            subjects.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(",", start);
        }
        subjects.push_back(line.substr(start, end));
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

    Database::~Database() {
    }

    Database::Database() {
    }
} // database