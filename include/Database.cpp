//
// Created by Parsa Jahanbani on 1/28/23.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Database.h"

using namespace std;
namespace database {
    ofstream fileOut;

    void insertUser() {
        fileOut.open("../data/users.txt", ios::out | ios::app);
        if (!fileOut.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }
        string username, firstName, lastName, password;
        cout << " ******* Add User *******" << endl;
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter First Name ";
        cin >> firstName;
        cout << "Enter Last Name: ";
        cin >> lastName;
        cout << "Enter Password: ";
        cin >> password;

        fileOut << username << ","
                << firstName << ","
                << lastName << ","
                << password << ","
                << endl;
        fileOut.close();
    }

    void insertBook() {
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

    void Database::insert(const std::string &input) {
        if (input=="users") {
            insertUser();
        } else if (input=="books") {
            insertBook();
        } else {
            cout << "Database::insert something went wrong" << endl;
        }
    }

    Database::~Database() {
        cout << "Database destructor called" << endl;
    }

    Database::Database() {
        cout << "Database constructor called" << endl;
    }
} // database