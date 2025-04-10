#include "signup.hpp"

#include <crow.h>
#include <crow/middlewares/cookie_parser.h>

#include "app-type.hpp"
#include "database.hpp"

void setupSignup(App& app, Database& database)
{
	CROW_ROUTE(app, "/login/").methods("GET"_method)([]()
	{
		return crow::mustache::load("login.html").render();
	});
	CROW_ROUTE(app, "/register/").methods("GET"_method)([]()
	{
		return crow::mustache::load("login.html").render();
	});

	// Register
	CROW_ROUTE(app, "/register/").methods("POST"_method)([&app, &database](const crow::request& request, crow::response& response)
	{
		string email = request.get_body_params().get("email");
		string password = request.get_body_params().get("password");

		if (database.insertUser(email, password))
		{
			authorize(app, request, response, database.getUserIdFromEmail(email));
		}
		else
		{
			crow::mustache::template_t page = crow::mustache::load("login.html");
			response.body = page.render({
				{"emailError", true},
				{"emailExists", true},
				{"email", email},
				{"password", password}
			}).dump();

			response.code = crow::CONFLICT;
		}

		response.end();
	});

	// Log in
	CROW_ROUTE(app, "/login/").methods("POST"_method)([&app, &database](const crow::request& request, crow::response& response)
	{
		string email = request.get_body_params().get("email");
		string password = request.get_body_params().get("password");

		if (database.validateUser(email, password))
		{
			authorize(app, request, response, database.getUserIdFromEmail(email));
		}
		else
		{
			crow::mustache::template_t page = crow::mustache::load("login.html");
			response.body = page.render({
				{"emailError", true},
				{"passwordError", true},
				{"email", email},
				{"password", password}
			}).dump();

			response.code = crow::UNAUTHORIZED;
		}

		response.end();
	});
}

void authorize(App& app, const crow::request& request, crow::response& response, const string& userId)
{
	app.get_context<crow::CookieParser>(request).set_cookie("token", generateToken(userId))
	                                            .path("/")
	                                            .httponly();

	response.add_header("Location", "/lessons/");
	response.code = crow::FOUND;
}