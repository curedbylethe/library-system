//
// Created by Parsa Jahanbani on 1/29/23.
//

#include "User.h"
#include "Database.h"
#include <iostream>
#include <random>
#include <sstream>
#include <string>


using namespace std;

namespace user {

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

    User::User(string &username, string &password, string &firstName, string &lastName, string& birthdate) {
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

    string User::getUuid() const {
        return this->uuid;
    }

    User::~User() {
    }

} // user