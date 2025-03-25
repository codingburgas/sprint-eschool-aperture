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

	CROW_BP_ROUTE(quizBlueprint, "/<string>")([&](crow::request request, const string& lessonTitle)
	{
		string token = app.get_context<crow::CookieParser>(request).get_cookie("token");
		string userId = jwt::decode(token).get_subject();
		
		string quizMaterial = database.getTextFromTextFile(lessonTitle, userId);

		crow::json::rvalue quizJson = generateQuiz(quizMaterial, userId);

		crow::mustache::template_t page = crow::mustache::load("quiz.html");
		crow::mustache::context renderContext;
		renderContext["questions"] = crow::json::wvalue(quizJson["questions"]).dump();
		return page.render(renderContext);
	});

	app.register_blueprint(quizBlueprint);
}

crow::json::rvalue QuizCreator::generateQuiz(const string& quizMaterial, const string& userId)
{
	crow::json::wvalue apiRequestBody;
	apiRequestBody["model"] = "llama-3.3-70b-versatile";
	apiRequestBody["response_format"]["type"] = "json_object";
	apiRequestBody["messages"][0]["role"] = "user";
	apiRequestBody["messages"][0]["content"] = "Read the text after the colon and generate 20 exam questions based on it. Your answer must be a JSON array of objects. Each object contains the keys \"question\", \"options\" and \"answer\". Here is the text: " + quizMaterial;

	cpr::Response apiResponse = cpr::Post(
		cpr::Url("https://api.groq.com/openai/v1/chat/completions"),
		cpr::Body(apiRequestBody.dump()),
		cpr::Header({ { "Content-Type", "application/json" } }),
		cpr::Bearer("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")
	);

	string generatedQuiz = crow::json::load(apiResponse.text)["choices"][0]["message"]["content"].s();
	quizJsons[userId] = generatedQuiz;

	return crow::json::load(cleanUpResponse(generatedQuiz));
}

string QuizCreator::cleanUpResponse(string& text)
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

	/* Fix escaped characters
	for (size_t escapeStart = text.find('\n'); escapeStart != string::npos; escapeStart = text.find('\\'))
	{
		if (text[escapeStart + 1] == 'n')
		{
			text.erase(escapeStart, 2);
		}
		if (text[escapeStart + 1] == '"')
		{
			text.erase(escapeStart, 1);
		}
	}*/

	return text;
}