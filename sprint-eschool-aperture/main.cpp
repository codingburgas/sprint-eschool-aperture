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

	CROW_ROUTE(app, "/login")([]() {
		crow::response res;
		res.set_static_file_info("static/html/login.html");
		return res;
	});

	CROW_ROUTE(app, "/media/fonts/Gefika.otf")([]() {
		crow::response res;
		res.set_static_file_info("static/media/fonts/Gefika.otf");
		return res;
	});

	CROW_ROUTE(app, "/media/videos/backgroundVideo.mp4")([]() {
		crow::response res;
		res.set_static_file_info("static/media/videos/backgroundVideo.mp4"); 
		return res;
	});

	app.multithreaded().run();
}