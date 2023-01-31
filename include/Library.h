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

    class Database {
    public:
        Database();
        ~Database();
        static void insertUser(string &username, string &firstName, string &lastName,
                               string &password, string &birthdate, string &role);
        static void setter(string &type, string &identifier, string &column, string &value);
        static void updateDataFile(const string &type, const string &identifier, int columnIndex, const string &value);
        static int getColumnIndex(const string &type, const string &column);


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
        vector<string> borrowed;
    public:
        User();
        ~User();
        User(string &username, string &password, string &firstName,
             string &lastName, string &birthdate);
        User(string &uuid, string &role, string &username,
             string &password, string &firstName, string &lastName, string &birthdate, vector<string> &borrowed);
        static pair<string, User> parseUserLine(const string& line);
        void setBorrowed(const string& bookUuid);
        [[nodiscard]] static map<string, User> loadUsersFromFile();
        [[nodiscard]] static User login();

        /* Getters */
        [[nodiscard]] string getUuid() const;
        [[nodiscard]] string getRole() const;
        [[nodiscard]] string getPassword() const;
        [[nodiscard]] vector<string> getBorrowed() const;

        /* Setters */
    };

    class Library {
    public:
        Library();
        ~Library();
        static void signUp();
        static void student(User &user);
        static void librarian();
        static void start();
        static void login();
        static void searchForBooks(User &user);
        static vector<string> split(const string &str, char del);
        static string join(vector<string> v, char delimiter);

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
        [[nodiscard]] static map<string, Book> searchBook();
        static void borrowBook(User& user, map<string, Book> *book_map = nullptr);

        /* Getters */
        [[nodiscard]] string getTitle() const;
        [[nodiscard]] string getEdition() const;
        [[nodiscard]] string getStatus() const;
        [[nodiscard]] vector<string> getAuthors() const;
        [[nodiscard]] string getIsbn() const;

        /* Setters */
        void setStatus(const string& s);
        void setBorrower(const string& b);

        /* Helpers */
        friend ostream &operator<<(ostream &out, const Book &book);
        [[nodiscard]] string printAuthors() const;
    };
} // library

#endif //LIBRARY_LIBRARY_H
