#include "lessons.hpp"

#include <crow.h>
#include <crow/middlewares/session.h>

#include "app.hpp"

void setupLessons(App& app, crow::Blueprint& lessonsBlueprint)
{
	if (lessonsBlueprint.prefix() != "lessons")
		lessonsBlueprint = crow::Blueprint("lessons");
	crow::SessionMiddleware
	CROW_BP_ROUTE(lessonsBlueprint, "/")([]()
	{
		;
	});
}