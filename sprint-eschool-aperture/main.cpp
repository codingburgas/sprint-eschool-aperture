#include <crow.h>

#include "database.hpp"

int main()
{
	crow::SimpleApp app;
	Database database("database.db");

	CROW_ROUTE(app, "/")([]() {
		crow::response res;
		res.set_static_file_info("static/index.html");
		return res;
	});

	CROW_ROUTE(app, "/css/home.css")([]() {
		crow::response res;
		res.set_static_file_info("static/css/home.css");
		return res;
	});

	CROW_ROUTE(app, "/login").methods("GET"_method)([]() {
		return crow::mustache::load("login.html").render();
	});
	CROW_ROUTE(app, "/register").methods("GET"_method)([]() {
		return crow::mustache::load("login.html").render();
	});

	// Register
	CROW_ROUTE(app, "/register").methods("POST"_method)([&database](crow::request request) {
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
	CROW_ROUTE(app, "/login").methods("POST"_method)([&database](crow::request request) {
		crow::response response;
		return response;
	});

	CROW_ROUTE(app, "/css/login.css")([]() {
		crow::response res;
		res.set_static_file_info("static/css/login.css");
		return res;
	});

	CROW_ROUTE(app, "/lessons")([]() {
		crow::response response;
		response.set_static_file_info("static/html/lessons.html");
		return response;
	});

	CROW_ROUTE(app, "/css/lessons.css")([]() {
		crow::response response;
		response.set_static_file_info("static/css/lessons.css");
		return response;
	});

	CROW_ROUTE(app, "/media/fonts/Gefika.otf")([]() {
		crow::response res;
		res.set_static_file_info("static/media/fonts/Gefika.otf");
		res.set_header("Content-Type", "font/otf");
		return res;
	});

	CROW_ROUTE(app, "/media/videos/backgroundVideo.mp4")([]() {
		crow::response res;
		res.set_static_file_info("static/media/videos/backgroundVideo.mp4"); 
		return res;
	});

	CROW_ROUTE(app, "/media/images/Peter.png")([]() {
		crow::response res;
		res.set_static_file_info("static/media/images/Peter.png");
		return res;
	});


	CROW_ROUTE(app, "/media/images/Mark.jpg")([]() {
		crow::response res;
		res.set_static_file_info("static/media/images/Mark.jpg");
		return res;
	});


	CROW_ROUTE(app, "/media/images/Kiril.jpg")([]() {
		crow::response res;
		res.set_static_file_info("static/media/images/Kiril.jpg");
		return res;
	});


	CROW_ROUTE(app, "/media/images/Hristian.jpg")([]() {
		crow::response res;
		res.set_static_file_info("static/media/images/Hristian.jpg");
		return res;
	});

	app.multithreaded().run();
}