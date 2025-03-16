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

private:
	sqlite::database database;
};