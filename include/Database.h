//
// Created by Parsa Jahanbani on 1/28/23.
//

#ifndef LIBRARY_DATABASE_H
#define LIBRARY_DATABASE_H

using namespace std;

namespace database {

    class Database {
    public:
        Database();
        ~Database();
        static void insertUser(string &username, string &firstName, string &lastName,
                               string &password, string &birthdate, string &role);
        static void insertBook();
    };

} // database

#endif //LIBRARY_DATABASE_H
