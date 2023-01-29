//
// Created by Parsa Jahanbani on 1/30/23.
//

#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H
#include <string>
#include <map>

using namespace std;
namespace library {

    class Library {
    public:
        Library();
        ~Library();
        static void signUp();
        static void student();
        static void librarian();
        static void start();
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
        string role;
        string username;
        string password;
        string firstName;
        string lastName;
        string birthdate;
    public:
        User(string &username, string &password, string &firstName,
             string &lastName, string &birthdate);
        User(string &uuid, string &role, string &username,
             string &password, string &firstName, string &lastName, string &birthdate);
        User();
        ~User();
        [[nodiscard]] static map<string, User> loadUsersFromFile();
        [[nodiscard]] static User login(const map<string, User>& user_map);

        /* Getters */
        [[nodiscard]] string getUuid() const;
        [[nodiscard]] string getRole() const;
        [[nodiscard]] string getUsername() const;
        [[nodiscard]] string getPassword() const;
        [[nodiscard]] string getFirstName() const;
        [[nodiscard]] string getLastName() const;
        [[nodiscard]] string getBirthdate() const;
    };



} // library

#endif //LIBRARY_LIBRARY_H
