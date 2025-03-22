#include "js.hpp"

#include <string>

#include <crow.h>

#include "app.hpp"

using namespace std;

void setupJS(App& app, crow::Blueprint& jsBlueprint)
{
	if (jsBlueprint.prefix() != "js")
		jsBlueprint = crow::Blueprint("js");

	CROW_BP_ROUTE(jsBlueprint, "/<string>")([](const string& jsFile)
		{
			crow::response response;
			response.set_static_file_info("static/js/" + jsFile);
			return response;
		});

	app.register_blueprint(jsBlueprint);
}