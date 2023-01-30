//
// Created by Parsa Jahanbani on 1/30/23.
//

#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
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
        static vector<string> split(const string &str, char del);
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

    class Book {
    private:
        string title, shelfNum, edition, publisher,
                year, isbn, length, status, borrower;
        vector<string> authors;
        vector<string> subjects;
    public:
        Book(string &title, vector<string> &authors, string &isbn, string &edition,
             string &publisher, vector<string> &subjects, string &length, string &year, string &status, string &borrower);
        Book();
        ~Book();
        [[nodiscard]] static map<string, Book> loadBooksFromFile();
        [[nodiscard]] static vector<Book> searchBook();
//        [[nodiscard]] static Book borrowBook(const map<string, Book>& book_map);
//        [[nodiscard]] static Book returnBook(const map<string, Book>& book_map);

        /* Getters */
        [[nodiscard]] string getTitle() const;
        [[nodiscard]] string getEdition() const;
        [[nodiscard]] vector<string> getAuthors() const;
        [[nodiscard]] string getIsbn() const;
        /* Helpers */
        friend ostream &operator<<(ostream &out, const Book &book);
        [[nodiscard]] string printAuthors() const;
    };
} // library

#endif //LIBRARY_LIBRARY_H
