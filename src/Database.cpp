//
// Created by Parsa Jahanbani on 1/28/23.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Library.h"

using namespace std;
namespace library {
    ofstream fileOut;

    void Database::insertUser(User &user) {
        fileOut.open("../data/users.txt", ios::out | ios::app);
        if (!fileOut.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }

        fileOut << user.getUuid() << ","
                << user.getRole() << ","
                << user.getUsername() << ","
                << user.getFirstName() << ","
                << user.getLastName() << ","
                << user.getPassword() << ","
                << user.getBirthdate() << ","
                << "NULL" << endl;
        fileOut.close();
    }

    void Database::setter(string type, string identifier, string column, string value) {
        int columnIndex = -1;

        try {
            columnIndex = getColumnIndex(type, column);
        } catch (const exception &e) {
            cerr << e.what() << endl;
            return;
        }

        try {
            updateDataFile(type, identifier, columnIndex, value);
        } catch (const exception &e) {
            cerr << e.what() << endl;
        }
    }

    int Database::getColumnIndex(const string &type, const string &column) {
        ifstream schemaFile("../data/schema.txt");
        if (!schemaFile.is_open()) {
            throw runtime_error("Error opening schema.txt");
        }

        string line;
        int startLine = (type == "users") ? 1 : 2;
        for (int i = 1; i < startLine; i++) {
            getline(schemaFile, line);
        }
        getline(schemaFile, line);
        schemaFile.close();

        map<string, int> headers;
        int index = 0;
        for (const auto &header : Library::split(line, ',')) {
            headers[header] = index++;
        }

        auto it = headers.find(column);
        if (it == headers.end()) {
            throw runtime_error("Column not found in schema");
        }

        return it->second;
    }

    void Database::updateDataFile(const string &type, const string &identifier, int columnIndex, const string &value) {
        ifstream dataFile;
        ofstream tempFile;
        string dataFilename = (type == "users") ? "../data/users.txt" : "../data/books.txt";
        dataFile.open(dataFilename);
        tempFile.open("../data/temp.txt");
        if (!dataFile.is_open() || !tempFile.is_open()) {
            throw runtime_error("Error opening data file");
        }

        string line;
        while (getline(dataFile, line)) {
            auto fields = Library::split(line, ',');
            if (fields[0] == identifier || fields[1] == identifier || fields[6] == identifier) {
                fields[columnIndex] = value;
            }
            tempFile << Library::join(fields, ',') << endl;
        }
        dataFile.close();
        tempFile.close();

        remove(dataFilename.c_str());
        rename("../data/temp.txt", dataFilename.c_str());
    }

    Database::~Database() = default;

    Database::Database() = default;
} // database