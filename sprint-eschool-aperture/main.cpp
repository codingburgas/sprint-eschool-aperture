#include <crow.h>

int main()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([]() {
		crow::response res;
		res.set_static_file_info("static/index.html");
		return res;
	});

	CROW_ROUTE(app, "/home.css")([]() {
		crow::response res;
		res.set_static_file_info("static/home.css");
		return res;
	});

	CROW_ROUTE(app, "/about.html")([]() {
		crow::response res;
		res.set_static_file_info("static/about.html");
		return res;
	});

	app.multithreaded().run();
}