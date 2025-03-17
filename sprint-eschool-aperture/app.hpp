#pragma once

#include <crow.h>
#include <crow/middlewares/cookie_parser.h>

#include "database.hpp"

using App = crow::App<crow::CookieParser>;

class ApertureNotepad
{
public:
	ApertureNotepad();

	void run();

private:
	App app;
	Database database;

	crow::Blueprint cssBlueprint;
	crow::Blueprint mediaBlueprint;
	crow::Blueprint lessonsBlueprint;

	void setupApp();
};