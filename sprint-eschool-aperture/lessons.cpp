#include "lessons.hpp"

#include <crow.h>
#include <crow/middlewares/cookie_parser.h>
#include <jwt-cpp/jwt.h>

#include "app-type.hpp"
#include "authentication.hpp"
#include "database.hpp"

void setupLessons(App& app, crow::Blueprint& lessonsBlueprint, Database& database)
{
	if (lessonsBlueprint.prefix() != "lessons")
		lessonsBlueprint = crow::Blueprint("lessons");

	lessonsBlueprint.CROW_MIDDLEWARES(app, Authentication);

	CROW_BP_ROUTE(lessonsBlueprint, "/").methods("GET"_method)([]()
	{
		crow::response response;
		response.set_static_file_info("static/html/lessons.html");
		return response;
	});

	CROW_BP_ROUTE(lessonsBlueprint, "/").methods("POST"_method)([&app, &database](const crow::request& request)
	{
		string token = app.get_context<crow::CookieParser>(request).get_cookie("token");
		string userId = jwt::decode(token).get_subject();

		database.createLesson(userId, request.get_body_params().get("title"));

		return crow::response();
	});

	CROW_BP_ROUTE(lessonsBlueprint, "/").methods("PUT"_method)([&app, &database](const crow::request& request)
	{
		string token = app.get_context<crow::CookieParser>(request).get_cookie("token");
		string userId = jwt::decode(token).get_subject();
		crow::json::rvalue lesson = crow::json::load(request.body);

		database.createLessonTextFile(lesson["lessonTitle"].s(), userId, lesson["lessonContent"].s());
		
		return crow::response();
	});

	CROW_BP_ROUTE(lessonsBlueprint, "/lesson/<string>").methods("GET"_method)([&app, &database](const crow::request& request, const string& lessonTitle)
	{
		string token = app.get_context<crow::CookieParser>(request).get_cookie("token");
		string userId = jwt::decode(token).get_subject();

		return database.getTextFromTextFile(lessonTitle, userId);
	});

	CROW_BP_ROUTE(lessonsBlueprint, "/names/").methods("GET"_method)([&app, &database](const crow::request& request)
	{
		string token = app.get_context<crow::CookieParser>(request).get_cookie("token");
		string userId = jwt::decode(token).get_subject();
		return database.getUsersLessons(userId);
	});

	app.register_blueprint(lessonsBlueprint);
}