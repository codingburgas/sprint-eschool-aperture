#include "lessons.hpp"

#include <crow.h>

#include "app.hpp"
#include "authentication.hpp"

void setupLessons(App& app, crow::Blueprint& lessonsBlueprint)
{
	if (lessonsBlueprint.prefix() != "lessons")
		lessonsBlueprint = crow::Blueprint("lessons");

	lessonsBlueprint.CROW_MIDDLEWARES(app, Authentication);

	CROW_BP_ROUTE(lessonsBlueprint, "")([]()
	{
		crow::response response;
		response.set_static_file_info("static/html/lessons.html");
		return response;
	});

	app.register_blueprint(lessonsBlueprint);
}