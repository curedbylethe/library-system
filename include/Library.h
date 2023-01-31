//
// Created by Parsa Jahanbani on 1/30/23.
//

#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
namespace library {

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
             string &lastName, string &birthdate, string &role);
        User(string &uuid, string &role, string &username,
             string &password, string &firstName, string &lastName, string &birthdate, vector<string> &borrowed);
        [[nodiscard]] static User login();
        void returnBook(string bookUuid);

        /* Getters */
        [[nodiscard]] string getUuid() const;
        [[nodiscard]] string getUsername() const;
        [[nodiscard]] string getFirstName() const;
        [[nodiscard]] string getLastName() const;
        [[nodiscard]] string getBirthdate() const;
        [[nodiscard]] string getRole() const;
        [[nodiscard]] string getPassword() const;
        [[nodiscard]] vector<string> getBorrowed() const;


        /* Setters */
        void setBorrowed(const string &bookUuid);

        /* Helpers */
        static pair<string, User> parseUserLine(const string &line);
        [[nodiscard]] static map<string, User> loadUsersFromFile();
        string borrowedBooksToString();
    };

    class Library {
    public:
        Library();
        ~Library();
        static void signUp();
        static void login();
        static void searchForBooks(User &user);
        static void borrow(User &user);
        static void returnBook(User &user);
        static void addNewBook();
        static void removeBook();
        static void removeUser();
        static void addUser(User &admin);

        /* UI */
        static void student(User &user);
        static void librarian(User &user);
        static void start();

        /* Helpers */
        static vector<string> split(const string &str, char del);
        static string join(vector<string> v, char delimiter);
        static string trim(string &s);
    };

    class Book {
    private:
        string title, shelfNum, edition, publisher,
                year, isbn, length, status, borrower;
        vector<string> authors;
        vector<string> subjects;
    public:
        Book();
        Book(string &title, string &shelfNum, vector<string> &authors, string &isbn, string &edition,
             string &publisher, vector<string> &subjects, string &length, string &year, string &status, string &borrower);
        Book(string &title, string &shelfNum, vector<string> &authors, string &isbn, string &edition,
             string &publisher, vector<string> &subjects, string &length, string &year);
        ~Book();
        static void borrowBook(User& user, map<string, Book> *book_map = nullptr);

        /* Getters */
        [[nodiscard]] string getTitle() const;
        [[nodiscard]] string getEdition() const;
        [[nodiscard]] string getStatus() const;
        [[nodiscard]] vector<string> getAuthors() const;
        [[nodiscard]] string getIsbn() const;
        [[nodiscard]] string getPublisher() const;
        [[nodiscard]] string getPublishedYear() const;
        [[nodiscard]] string getLength() const;
        [[nodiscard]] vector<string> getSubjects() const;
        [[nodiscard]] string getShelfNum() const;

        /* Setters */
        void setStatus(const string& s);
        void setBorrower(const string& b);

        /* Helpers */
        friend ostream &operator<<(ostream &out, const Book &book);
        [[nodiscard]] string printAuthors() const;
        [[nodiscard]] static map<string, Book> loadBooksFromFile();
        [[nodiscard]] static map<string, Book> searchBook();
    };

    class Database {
    public:
        Database();
        ~Database();
        static void insertUser(User &user);
        static void insertBook(Book &book);
        static void deleteLine(string type, string identifier);
        static void setter(string type, string identifier, string column, string value);
        static void updateDataFile(const string &type, const string &identifier, int columnIndex, const string &value);
        static int getColumnIndex(const string &type, const string &column);
    };
} // library

#endif //LIBRARY_LIBRARY_H
