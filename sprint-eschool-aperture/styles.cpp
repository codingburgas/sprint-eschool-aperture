#include "styles.hpp"

#include <string>

#include <crow.h>

#include "app.hpp"

using namespace std;

void setupCSS(App& app, crow::Blueprint& cssBlueprint)
{
	if (cssBlueprint.prefix() != "css")
		cssBlueprint = crow::Blueprint("css");

	CROW_BP_ROUTE(cssBlueprint, "/<string>")([](string cssFile)
	{
		crow::response response;
		response.set_static_file_info("static/css/" + cssFile);
		return response;
	});

	app.register_blueprint(cssBlueprint);
}