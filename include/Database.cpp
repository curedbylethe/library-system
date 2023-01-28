//
// Created by Parsa Jahanbani on 1/28/23.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ranges>
#include "Database.h"

using namespace std;
namespace database {
    void Database::insert(const std::string &input) {
        ofstream fileOut;
        switch (input=="users") {
            case 1: {
                fileOut.open("../data/users.txt", ios::out | ios::app);
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
                break;
            }
            case 0: {
                fileOut.open("../data/books.txt", ios::out | ios::app);
                string title, edition, publisher;
                int publishedYear, shelfNumber, isbn, length;
                vector<string> subjects, authors;
                cout << " ******* Add a Book *******" << endl;
                cout << "Enter Title: ";
                cin >> title;
                cout << "Enter Shelf Number: ";
                cin >> shelfNumber;
                cout << "Enter Authors (separated by commas): ";
                string line;
                getline(cin, line);
                for (auto author : line | views::split(',')) {
                    authors.push_back(author);
                }
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
                cout << "Enter Subjects: ";
                getline(cin, line);
                for (auto subject : line | views::split(',')) {
                    subjects.push_back(subject);
                }


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
                break;
            }
        }
    }

    Database::~Database() {
        cout << "Database destructor called" << endl;
    }

    Database::Database() {
        cout << "Database constructor called" << endl;
    }
} // database