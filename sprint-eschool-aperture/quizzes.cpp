#include "quizzes.hpp"

#include <string>

#include <crow.h>
#include <crow/middlewares/cookie_parser.h>
#include <cpr/cpr.h>
#include <jwt-cpp/jwt.h>

#include "app-type.hpp"
#include "database.hpp"

using namespace std;

void QuizCreator::setupQuizzes(App& app, crow::Blueprint& quizBlueprint, Database& database)
{
	if (quizBlueprint.prefix() != "quiz")
		quizBlueprint = crow::Blueprint("quiz", "static", "templates");

	// Generate quiz from lesson
	CROW_BP_ROUTE(quizBlueprint, "/<string>").methods("GET"_method)([&](const crow::request& request, const string& lessonTitle)
	{
		string token = app.get_context<crow::CookieParser>(request).get_cookie("token");
		string userId = jwt::decode(token).get_subject();
		string quizMaterial = database.getTextFromTextFile(lessonTitle, userId);
		
		crow::json::wvalue quizJson = setupQuiz(quizMaterial, userId);

		crow::mustache::template_t page = crow::mustache::load("quiz.html");
		crow::mustache::context renderContext;
		renderContext["questions"] = crow::json::wvalue(quizJson["questions"]).dump();
		return page.render(renderContext);
	});

	// Grade the quiz
	CROW_BP_ROUTE(quizBlueprint, "/<string>").methods("POST"_method)([&](const crow::request& request, const string& lessonTitle)
	{
		string token = app.get_context<crow::CookieParser>(request).get_cookie("token");
		string userId = jwt::decode(token).get_subject();

		crow::json::rvalue userChoices = crow::json::load(request.body);
		string answers = getQuizAnswers(userId);
		int correctChoices = 0;

		for (size_t i = 0; i < userChoices.size(); i++)
		{
			if (answers.find(userChoices[i].s()) != string::npos)
			{
				correctChoices++;
			}
		}

		crow::json::wvalue response;
		response["grade"] = calculateGrade(correctChoices, userChoices.size());
		response["points"] = correctChoices;
		return response;
	});

	app.register_blueprint(quizBlueprint);
}

crow::json::wvalue QuizCreator::setupQuiz(const string& quizMaterial, const string& userId)
{
	string apiResponse = generateQuiz(quizMaterial)["choices"][0]["message"]["content"].s();
	crow::json::wvalue quizJson = crow::json::load(cleanUpResponse(apiResponse));

	setQuizAnswers(userId, removeAnswers(quizJson));

	return quizJson;
}

crow::json::rvalue QuizCreator::generateQuiz(const string& quizMaterial)
{
	crow::json::wvalue apiRequestBody;
	apiRequestBody["model"] = "llama-3.3-70b-versatile";
	apiRequestBody["response_format"]["type"] = "json_object";
	apiRequestBody["messages"][0]["role"] = "user";
	apiRequestBody["messages"][0]["content"] = "Read the text after the colon and generate 20 exam questions based on it. Your answer must be a JSON array of objects. Each object contains the keys \"question\", \"options\" and \"answer\". Here is the text: " + quizMaterial;

	cpr::Response apiResponse;

	do
	{
		apiResponse = cpr::Post(
			cpr::Url("https://api.groq.com/openai/v1/chat/completions"),
			cpr::Body(apiRequestBody.dump()),
			cpr::Header({ { "Content-Type", "application/json" } }),
			cpr::Bearer("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")
		);
	}
	while (apiResponse.text.find("question") == string::npos);

	return crow::json::load(apiResponse.text);
}

string QuizCreator::removeAnswers(crow::json::wvalue& quizJson)
{
	string answers = "";

	for (size_t i = 0; i < quizJson["questions"].size(); i++)
	{
		answers += quizJson["questions"][i]["answer"].dump();
		quizJson["questions"][i]["answer"].reset();
	}

	return answers;
}

void QuizCreator::setQuizAnswers(const string& userId, const string& answers)
{
	quizAnswers[userId] = answers;
}

string QuizCreator::getQuizAnswers(const string& userId)
{
	return quizAnswers[userId];
}

string QuizCreator::calculateGrade(float receivedPoints, float totalPoints)
{
	float percent = receivedPoints / totalPoints * 100;

	if (percent >= 90)
	{
		return "Excellent 6";
	}
	else if (percent >= 85)
	{
		return "Very Good 5";
	}
	else if (percent >= 80)
	{
		return "Good 4";
	}
	else if (percent >= 75)
	{
		return "Poor 3";
	}
	else
	{
		return "Very Poor 2";
	}
}

string QuizCreator::cleanUpResponse(string text)
{
	// Remove whitespace
	for (size_t i = 0; i < text.length(); i++)
	{
		if (text[i] == ' ' && text[i + 1] == ' ')
		{
			do
			{
				text.erase(i + 1, 1);
			}
			while (text[i + 1] == ' ');
		}
	}

	return text;
}