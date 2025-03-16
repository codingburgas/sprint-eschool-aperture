#include "database.hpp"

#include <iostream>
#include <string>

#include <bcryptcpp.h>
#include <sqlite_modern_cpp.h>

using namespace std;

Database::Database(const string& databaseName)
	: database(sqlite::database(databaseName))
{
	database << "CREATE TABLE IF NOT EXISTS users ("
	            "	id INTEGER PRIMARY KEY AUTOINCREMENT,"
	            "	email TEXT NOT NULL UNIQUE,"
	            "	password TEXT NOT NULL);";
}

bool Database::insertUser(const string& email, const string& password)
{
	string hashedPassword = bcrypt::generateHash(password);

	try
	{
		database << "INSERT INTO users (email, password) VALUES (?, ?);"
		         << email
		         << hashedPassword;

		cout << "User added.\n";

		return true;
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
		return false;
	}
}

bool Database::validateUser(const string& email, const string& password)
{
	string storedHash;

	try
	{
		database << "SELECT password FROM users WHERE email = '?';"
			     << email
			     >> storedHash;

		return bcrypt::validatePassword(password, storedHash);
	}
	catch (const exception& e)
	{
		cerr << e.what() << endl;
		return false;
	}
}