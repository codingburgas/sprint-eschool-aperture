#pragma once

#include <crow.h>
#include <crow/middlewares/cookie_parser.h>

#include "authentication.hpp"
#include "database.hpp"

using App = crow::App<crow::CookieParser, Authentication>;

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