//
// Created by Parsa Jahanbani on 1/29/23.
//

#include "Library.h"
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <map>

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
               string &lastName, string& birthdate) {
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
    }

    User::User(string &uuid, string &role, string &username,
               string &password, string &firstName, string &lastName, string &birthdate) {
        this->uuid = uuid;
        this->username = username;
        this->password = password;
        this->firstName = firstName;
        this->lastName = lastName;
        this->birthdate = birthdate;
    }

    map<string, User> User::loadUsersFromFile() {
        map<string, User> user_map;
        ifstream file("../data/users.txt");
        if (!file.is_open()) {
            throw runtime_error("Failed to open file");
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string uuid, role, username, password, firstname, lastname, birthdate;
            getline(iss, uuid, ',');
            getline(iss, role, ',');
            getline(iss, username, ',');
            getline(iss, firstname, ',');
            getline(iss, lastname, ',');
            getline(iss, password, ',');
            getline(iss, birthdate);
            User user(uuid, role, username, password, firstname, lastname, birthdate);
            user_map[username] = user;
        }

        return user_map;

    }

    User User::login(const map<string, User>& user_map) {
        string username, password;

        while (true) {
            cout << "Enter username: ";
            cin >> username;
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


    string User::getUuid() const {
        return this->uuid;
    }
    string User::getRole() const {
        return this->role;
    }
    string User::getUsername() const {
        return this->username;
    }
    string User::getPassword() const {
        return this->password;
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
    User::~User() {
    }
} // user