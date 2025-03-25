#pragma once

#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_modern_cpp.h>

using namespace std;

class Database
{
public:
	Database(const string& databaseName);

	bool insertUser(const string& email, const string& password);
	bool validateUser(const string& email, const string& password);
	string getUserIdFromEmail(const string& email);
	bool createLesson(const string& userId, const string& lessonTitle);
	crow::json::wvalue getUsersLessons(const string& userId);
	void createLessonTextFile(const string& lessonTitle, const string& userId, const string& lessonContent = "");
	string getTextFromTextFile(const string& lessonTitle, const string& userId);

private:
	sqlite::database database;
	bool validateEmail(const string& email);
};