#include "media.hpp"

#include <string>

#include <crow.h>

#include "app.hpp"

void setupMedia(App& app, crow::Blueprint& mediaBlueprint)
{
	if (mediaBlueprint.prefix() != "media")
		mediaBlueprint = crow::Blueprint("media");

	CROW_BP_ROUTE(mediaBlueprint, "/<path>")([](string file)
	{
		crow::response response;
		response.set_static_file_info("static/media/" + file);
		return response;
	});

	app.register_blueprint(mediaBlueprint);
}