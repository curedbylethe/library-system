//
// Created by Parsa Jahanbani on 1/30/23.
//

#include "Library.h"
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <map>
#include <future>

using namespace std;

namespace library {
    Book::Book() = default;
    Book::~Book() = default;
    Book::Book(string &t, vector<string> &a, string &is, string &e,
               string &pub, vector<string> &subs, string &l, string &y, string &stat, string &b) :
                   title(t), isbn(is), subjects(subs), edition(e), publisher(pub),
                   year(y), status(stat), borrower(b), length(l), authors(a) {};

    map<string, Book> Book::loadBooksFromFile() {
        map<string, Book> books_map;
        ifstream file("../data/books.txt");
        if (!file.is_open()) {
            throw runtime_error("Failed to open file");
        }
        string line;

        while (getline(file, line)) {
            istringstream iss(line);
            string title, shelfNum, authors, edition, publisher, year,
                    isbn, length, subjects, status, borrower;
            getline(iss, title, ',');
            getline(iss, shelfNum, ',');
            getline(iss, authors, ',');
            getline(iss, edition, ',');
            getline(iss, publisher, ',');
            getline(iss, year, ',');
            getline(iss, isbn, ',');
            getline(iss, length, ',');
            getline(iss, subjects, ',');
            getline(iss, status, ',');
            getline(iss, borrower, ',');

            vector<string> subjectsVect = Library::split(subjects, '-');
            vector<string> authorsVect = Library::split(authors, '-');

            Book book(title, authorsVect, isbn, edition, publisher, subjectsVect, length, year, status, borrower);
            books_map[title] = book;
        }
        return books_map;
    }

    vector<Book> Book::searchBook() {
        auto future = async(launch::async, &Book::loadBooksFromFile);
        string title;
        cin.ignore();
        cout << "Enter the title of the book: ";
        getline(cin, title);
        map<string, Book> books_map = future.get();
        vector<Book> results;
        for (const auto &[key, value] : books_map) {
            if (key == title) {
                results.push_back(value);
            }
        }
        if (results.empty()) {
            throw runtime_error("Book not found");
        } else {
            return results;
        }
    }

    /* Getter */

    vector<string> Book::getAuthors() const {
        return this->authors;
    }
    string Book::getIsbn() const {
        return this->isbn;
    }

    /* Helpers */
    string Book::printAuthors() const {
        string authors_str;
        for (const auto &author : this->getAuthors()) {
            authors_str += author + ", ";
        }
        return authors_str;

    }

    ostream &operator<<(ostream &out, const Book &book) {
        return out << "Book ID: " << book.getIsbn() << ". " << book.getTitle() << " by " << book.printAuthors() << "edition: " << book.getEdition();
    }

    string Book::getTitle() const {
        return this->title;
    }

    string Book::getEdition() const {
        return this->edition;
    }


}