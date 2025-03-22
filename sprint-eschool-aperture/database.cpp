#include "database.hpp"

#include <string>

#include <crow.h>
#include <bcryptcpp.h>
#include <sqlite_modern_cpp.h>

using namespace std;

Database::Database(const string& databaseName)
	: database(sqlite::database(databaseName))
{
	//Add table for users
	database << "CREATE TABLE IF NOT EXISTS users ("
	            "	user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
	            "	email TEXT NOT NULL UNIQUE,"
	            "	password TEXT NOT NULL);";

	// Add table for the lesson files
	database << "CREATE TABLE IF NOT EXISTS lessons ("
	            "	user_id INTEGER,"
	            "	title TEXT NOT NULL UNIQUE,"
	            "	file_path TEXT NOT NULL UNIQUE,"
	            "	FOREIGN KEY (user_id) REFERENCES users(user_id));"; 
} 

bool Database::insertUser(const string& email, const string& password)
{

	if (!validateEmail(email))
	{
		return false;
	}

	try
	{
		database << "INSERT INTO users (email, password) VALUES (?, ?);" // Prepared statement for inserting users email and password
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

bool Database::validateEmail(const string& email)
{
	return email.find('@') != string::npos and email.find('.') != string::npos;
}

string Database::getUserId(const string& email)
{
	string userId;

	database << "SELECT user_id FROM users WHERE email = ?;"
	         << email
	         >> userId;

	return userId;
}