//
// Created by Parsa Jahanbani on 1/29/23.
//

#ifndef LIBRARY_USER_H
#define LIBRARY_USER_H

#include <string>
#include <vector>
using namespace std;

namespace user {

    class User {
    private:
        string uuid;
        string username;
        string password;
        string firstName;
        string lastName;
        string birthdate;

    public:
        User(string &username, string &password, string &firstName, string &lastName, string &birthdate);
        User();
        ~User();
        /* Getters */
        [[nodiscard]] string getUuid() const;
    };

} // user

#endif //LIBRARY_USER_H
