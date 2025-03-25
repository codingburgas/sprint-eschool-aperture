#include "app.hpp"

#include <crow.h>

#include "app-type.hpp"
#include "database.hpp"
#include "styles.hpp"
#include "js.hpp"
#include "media.hpp"
#include "signup.hpp"
#include "lessons.hpp"
#include "quizzes.hpp"

ApertureNotepad::ApertureNotepad()
	: app()
	, database("database.db")
	, cssBlueprint("css")
	, jsBlueprint("js")
	, mediaBlueprint("media")
	, lessonsBlueprint("lessons")
	, quizBlueprint("quiz", "static", "templates")
	, quizCreator()
{
	setupApp();
}

void ApertureNotepad::setupApp()
{
	setupJs(app, jsBlueprint);
	setupCss(app, cssBlueprint);
	setupMedia(app, mediaBlueprint);
	setupSignup(app, database);
	setupLessons(app, lessonsBlueprint, database);
	quizCreator.setupQuizzes(app, quizBlueprint, database);

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