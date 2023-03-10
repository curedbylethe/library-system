//
// Created by Parsa Jahanbani on 1/29/23.
//

#include "Library.h"
#include <iostream>
#include <random>
#include <map>
#include <future>

using namespace std;

namespace library {

    User::User() {
        random_device rd;
        mt19937 gen(rd());
        mt19937::result_type seed = rd();
        gen.seed(seed);
        uniform_int_distribution<> dis(0, 15);

        stringstream ss;
        ss << hex << dis(gen) << dis(gen) << dis(gen) << dis(gen) << "-";
        ss << hex << dis(gen) << dis(gen) << "-";
        ss << hex << dis(gen) << dis(gen) << "-";
        ss << hex << dis(gen) << dis(gen) << "-";
        ss << hex << dis(gen) << dis(gen) << dis(gen) << dis(gen)
           << dis(gen) << dis(gen);

        this->uuid = ss.str();
    }

    User::User(string &username, string &password, string &firstName,
               string &lastName, string& birthdate, string &role) {
        random_device rd;
        mt19937 gen(rd());
        mt19937::result_type seed = rd();
        gen.seed(seed);
        uniform_int_distribution<> dis(0, 15);

        stringstream ss;
        ss << hex << dis(gen) << dis(gen) << dis(gen) << dis(gen) << "-";
        ss << hex << dis(gen) << dis(gen) << "-";
        ss << hex << dis(gen) << dis(gen) << "-";
        ss << hex << dis(gen) << dis(gen) << "-";
        ss << hex << dis(gen) << dis(gen) << dis(gen) << dis(gen)
           << dis(gen) << dis(gen);

        this->username = username;
        this->password = password;
        this->firstName = firstName;
        this->lastName = lastName;
        this->birthdate = birthdate;
        this->uuid = ss.str();
        this->role = role;
    }

    User::User(string &uuid, string &role, string &username,
               string &password, string &firstName, string &lastName, string &birthdate, vector<string> &borrowed) {
        this->uuid = uuid;
        this->username = username;
        this->password = password;
        this->firstName = firstName;
        this->lastName = lastName;
        this->birthdate = birthdate;
        this->role = role;
        if (borrowed[0] != "NULL") {
            this->borrowed = borrowed;
        }
    }

    void User::returnBook(string bookUuid) {
        bookUuid = Library::trim(bookUuid);
        for (int i = 0; i < this->borrowed.size(); i++) {
            if (this->borrowed[i] == bookUuid) {
                this->borrowed.erase(this->borrowed.begin() + i);
                break;
            }
        }
        auto b = this->borrowedBooksToString();
        if (b == "") {
            b = "NULL";
        }
        Database::setter("users", this->uuid, "borrowed", b);
        Database::setter("books", bookUuid, "borrower", "NULL");
        Database::setter("books", bookUuid, "status", "free");
    }

    User User::login() {
        auto future = async(launch::async, &User::loadUsersFromFile);
        string username, password;

        while (true) {
            cout << "Enter username: ";
            cin >> username;
            map<string, User> user_map = future.get();
            auto it = user_map.find(username);
            if (it == user_map.end()) {
                cout << "Username not found" << endl;
                continue;
            }
            cout << "Enter password: ";
            cin >> password;
            User user = it->second;
            if (user.getPassword() != password) {
                char choice;
                cout << "Incorrect password" << endl;
                cout << "\nDo you wish to try again? (y/n): ";
                cin >> choice;
                if (choice == 'n') {
                    Library::start();
                } else if (choice == 'y') {
                    continue;
                } else {
                    cout << "Invalid choice" << endl;
                    continue;
                }
                continue;
            }

            return user;
        }
    }

    /* Getters */
    string User::getUuid() const {
        return this->uuid;
    }
    string User::getRole() const {
        return this->role;
    }
    string User::getPassword() const {
        return this->password;
    }
    vector<string> User::getBorrowed() const {
        return this->borrowed;
    }
    string User::getUsername() const {
        return this->username;
    }
    string User::getFirstName() const {
        return this->firstName;
    }
    string User::getLastName() const {
        return this->lastName;
    }
    string User::getBirthdate() const {
        return this->birthdate;
    }


    /* Setters */
    void User::setBorrowed(const string& bookUuid) {
        this->borrowed.push_back(bookUuid);
        auto b = this->borrowedBooksToString();
        Database::setter("users", this->getUuid(), "borrowed", b);
    }

    /* Helpers */
    string User::borrowedBooksToString() {
        auto b = this->getBorrowed();
        string value;
        for (auto &i : b) {
            if (i == b.back())
                value += i;
            else
                value += i + "-";
        }
        return value;
    }

    map<string, User> User::loadUsersFromFile() {
        map<string, User> user_map;
        ifstream file("../data/users.txt");
        if (!file.is_open()) {
            throw runtime_error("Failed to open file");
        }

        string line;
        while (getline(file, line)) {
            auto it = User::parseUserLine(line);
            user_map[it.first] = it.second;
        }
        return user_map;
    }

    pair<string, User> User::parseUserLine(const string& line) {
        pair<string, User> user_map;
        istringstream iss(line);
        string uuid, role, username, password, firstname, lastname, birthdate, borrowed;
        getline(iss, uuid, ',');
        getline(iss, role, ',');
        getline(iss, username, ',');
        getline(iss, firstname, ',');
        getline(iss, lastname, ',');
        getline(iss, password, ',');
        getline(iss, birthdate, ',');
        getline(iss, borrowed);
        vector<string> borrowedBooks = Library::split(borrowed, '-');
        const User user(uuid, role, username, password, firstname, lastname, birthdate, borrowedBooks);
        user_map.first = username;
        user_map.second = user;
        return user_map;
    }

    User::~User() = default;

} // user