//
// Created by Parsa Jahanbani on 1/30/23.
//

#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H
#include <string>

using namespace std;
namespace library {

    class Library {
    public:
        Library();
        ~Library();
        void signUp() const;
        void start() const;
    };

    class Database {
    public:
        Database();
        ~Database();
        static void insertUser(string &username, string &firstName, string &lastName,
                               string &password, string &birthdate, string &role);
        static void insertBook();
    };

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



} // library

#endif //LIBRARY_LIBRARY_H
