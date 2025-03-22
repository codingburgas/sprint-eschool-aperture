#pragma once

#include <string>

#include <sqlite_modern_cpp.h>

using namespace std;

class Database
{
public:
	Database(const string& databaseName);

	bool insertUser(const string& email, const string& password);
	bool validateUser(const string& email, const string& password);
	string getUserIdFromEmail(const string& email);

private:
	sqlite::database database;
	bool validateEmail(const string& email);
};