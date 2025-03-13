#include <crow.h>

int main()
{
	crow::SimpleApp app;

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

	CROW_ROUTE(app, "/about")([]() {
		crow::response res;
		res.set_static_file_info("static/html/about.html");
		return res;
	});

	CROW_ROUTE(app, "/login").methods("GET"_method, "POST"_method)([](crow::request request) {
		crow::response response;

		if (request.method == "POST"_method)
		{
			return crow::response{ request.get_body_params().get("email") };
		}
		else
		{
			response.set_static_file_info("static/html/login.html");
			return response;
		}
	});

	CROW_ROUTE(app, "/css/login.css")([]() {
		crow::response res;
		res.set_static_file_info("static/css/login.css");
		return res;
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