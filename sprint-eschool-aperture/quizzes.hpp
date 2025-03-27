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
	unordered_map<string, string> quizAnswers;

	crow::json::wvalue setupQuiz(const string& quizMaterial, const string& userId); // Prepare a quiz for serving
	crow::json::rvalue generateQuiz(const string& quizMaterial); // Fetch quiz data
	string cleanUpResponse(string response); // Remove format characters from response
	string removeAnswers(crow::json::wvalue& quizJson); // Use this to safely send the quiz to the client. Returns the removed answers
	string getQuizAnswers(const string& userId); // Get the answers to the quiz the user is currently taking
	void setQuizAnswers(const string& userId, const string& answers); // Save the answers to the quiz the user is currently taking

	string calculateGrade(float receivedPoints, float totalPoints); // Calculate the grade using the grading system
};