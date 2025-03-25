#pragma once

#include <unordered_map>
#include <string>

#include <crow.h>

#include "app-type.hpp"
#include "database.hpp"

using namespace std;

class QuizCreator
{
public:
	void setupQuizzes(App& app, crow::Blueprint& quizBlueprint, Database& database);

private:
	unordered_map<string, string> quizJsons;

	crow::json::rvalue generateQuiz(const string& quizMaterial, const string& userId);
	string cleanUpResponse(string& response);
};