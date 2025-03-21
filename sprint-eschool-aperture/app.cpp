#include "app.hpp"

#include <crow.h>

#include "database.hpp"
#include "styles.hpp"
#include "js.hpp"
#include "media.hpp"
#include "signup.hpp"
#include "lessons.hpp"

ApertureNotepad::ApertureNotepad()
	: app()
	, database("database.db")
	, cssBlueprint("css")
	, jsBlueprint("js")
	, mediaBlueprint("media")
	, lessonsBlueprint("lessons")
{
	setupApp();
}

void ApertureNotepad::setupApp()
{
	setupJS(app, jsBlueprint);
	setupCSS(app, cssBlueprint);
	setupMedia(app, mediaBlueprint);
	setupSignup(app, database);
	setupLessons(app, lessonsBlueprint);

	CROW_ROUTE(app, "/")([]()
	{
		crow::response response;
		response.set_static_file_info("static/index.html");
		return response;
	});
}

void ApertureNotepad::run()
{
	app.multithreaded().run();
}