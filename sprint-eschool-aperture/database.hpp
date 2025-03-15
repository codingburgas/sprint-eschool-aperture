#pragma once

#include <iostream>

#include <string>

#include <sqlite3.h>
#include <bcrypt.h>

using namespace std;


class Database
{
 public:
	Database(const string& databaseName);
	~Database();

	bool insertUser(const string& username, const  string& password);
	bool validateUser(const std::string& email, const std::string& password);

private:
	sqlite3* database;

};