//
// Created by Parsa Jahanbani on 1/28/23.
//

#ifndef LIBRARY_DATABASE_H
#define LIBRARY_DATABASE_H

namespace database {

    class Database {
    public:
        Database();
        ~Database();
        static void insert(const std::string &input);
    };

} // database

#endif //LIBRARY_DATABASE_H
