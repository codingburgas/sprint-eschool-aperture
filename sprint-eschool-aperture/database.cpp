#include "database.hpp"

#include <iostream>
#include <string>

#include <sqlite3.h>
#include <bcryptcpp.h>

using namespace std;

Database::Database(const string& databaseName) {

        if (sqlite3_open(databaseName.c_str(), &database) != SQLITE_OK) {
            cerr << "Error opening database: " << sqlite3_errmsg(database) << endl;
        }
        else {
            cout << "Database opened successfully.\n";
        }

        const char* sql = "CREATE TABLE IF NOT EXISTS users ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "email TEXT NOT NULL UNIQUE, "
                          "password TEXT NOT NULL);";

        if (sqlite3_exec(database, sql, nullptr, nullptr, nullptr) != SQLITE_OK) {
            cerr << "Error creating table.\n";
        }
        else {
            cout << "Table created successfully.\n";
        }
}

Database::~Database() {
    sqlite3_close(database);
}

bool Database::insertUser(const string& email, const string& password) {

    string hashedPassword = bcrypt::generateHash(password);
    const char* sql = "INSERT INTO users (email, password) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(database) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error inserting user: " << sqlite3_errmsg(database) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    cout << "User added securely.\n";
    return true;
}

bool Database::validateUser(const std::string& email, const std::string& password) {

    string sql = "SELECT password FROM users WHERE email = '?';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(database, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(database) << endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_STATIC);


        if (sqlite3_step(stmt) == SQLITE_ROW) {
            string storedHash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            sqlite3_finalize(stmt);
            return bcrypt::validatePassword(password, storedHash);
          }

    sqlite3_finalize(stmt);
    return false;
}