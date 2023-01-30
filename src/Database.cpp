//
// Created by Parsa Jahanbani on 1/28/23.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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

    void Database::setter(string &type, string &identifier, string &column, string &value) {
        ifstream schemaFile("schema.txt");
        if (!schemaFile.is_open()) {
            cout << "Error opening schema.txt" << endl;
            return;
        }

        string line;
        int columnIndex = -1;

        /* Since the schema for users is on the first line and *
         * the schema for books is on the second line, we need *
         * to skip the first line if we're looking for a book  */
        if (type == "User") {
            getline(schemaFile, line);
            vector<string> headers = Library::split(line, ',');
            for (int i = 0; i < headers.size(); i++) {
                if (headers[i] == column) {
                    columnIndex = i;
                    break;
                }
            }
        } else if (type == "Book") {
            getline(schemaFile, line);
            getline(schemaFile, line);
            vector<string> headers = Library::split(line, ',');
            for (int i = 0; i < headers.size(); i++) {
                if (headers[i] == column) {
                    columnIndex = i;
                    break;
                }
            }
        }
        schemaFile.close();

        // Check if the column was found
        if (columnIndex == -1) {
            cout << "Column not found in schema" << endl;
            return;
        }

        ifstream dataFile;
        ofstream tempFile;
        string dataFilename;
        if (type == "user") {
            dataFilename = "../data/users.txt";
        } else if (type == "book") {
            dataFilename = "../data/books.txt";
        }
        dataFile.open(dataFilename);
        tempFile.open("../data/temp.txt");
        if (!dataFile.is_open() || !tempFile.is_open()) {
            cout << "Error opening data file" << endl;
            return;
        }

        bool found = false;
        while (getline(dataFile, line)) {
            vector<string> fields = Library::split(line, ',');
            /* For ease of use, we pass this->uuid and this->title *
             * as the identifier, so we only check the first field */
            if (fields[0] == identifier) {
                fields[columnIndex] = value;
                found = true;
            }
            tempFile << Library::join(fields, ',') << endl;
        }
        dataFile.close();
        tempFile.close();

        // Replace the original data file with the temp file
        remove(dataFilename.c_str());
        rename("temp.txt", dataFilename.c_str());

    }

    Database::~Database() = default;

    Database::Database() = default;
} // database