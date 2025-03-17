#include "database.hpp"

#include <iostream>
#include <string>

#include <crow.h>
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
	try
	{
		database << "INSERT INTO users (email, password) VALUES (?, ?);"
		         << email
		         << bcrypt::generateHash(password);

		CROW_LOG_INFO << "User added successfuly";

		return true;
	}
	catch (const sqlite::sqlite_exception& exception)
	{
		switch (exception.get_extended_code())
		{
		case SQLITE_CONSTRAINT_UNIQUE:
			return false;
		default:
			CROW_LOG_ERROR << exception.errstr();
			return false;
		}
	}
}

bool Database::validateUser(const string& email, const string& password)
{
	string storedHash;

	try
	{
		database << "SELECT password FROM users WHERE email = ?;"
			     << email
			     >> storedHash;

		return bcrypt::validatePassword(password, storedHash);
	}
	catch (const sqlite::sqlite_exception& exception)
	{
		CROW_LOG_ERROR << exception.errstr();
		return false;
	}
}