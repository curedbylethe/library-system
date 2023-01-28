#include <iostream>
#include "include/Database.h"

using namespace std;

int main() {
    database::Database db;
    db.insert("users");

    return 0;
}
