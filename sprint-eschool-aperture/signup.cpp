#include "signup.hpp"

#include <crow.h>

#include "app.hpp"
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
	CROW_ROUTE(app, "/register").methods("POST"_method)([&database](crow::request request)
	{
		crow::response response;

		if (database.insertUser(request.get_body_params().get("email"), request.get_body_params().get("password")))
		{
			response.set_header("Location", "/lessons");
			response.code = crow::FOUND;
		}
		else
		{
			crow::mustache::template_t page = crow::mustache::load("login.html");
			response = page.render({ {"emailError", true}, {"emailExists", true} });
			response.code = crow::CONFLICT;
		}

		return response;
	});

	// Log in
	CROW_ROUTE(app, "/login").methods("POST"_method)([&database](crow::request request)
	{
		crow::response response;
		return response;
	});
}