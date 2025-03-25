#pragma once

#include <crow.h>

#include "app-type.hpp"
#include "database.hpp"
#include "quizzes.hpp"

class ApertureNotepad
{
public:
	ApertureNotepad();

	void run();

private:
	App app;
	Database database;

	crow::Blueprint jsBlueprint;
	crow::Blueprint cssBlueprint;
	crow::Blueprint mediaBlueprint;
	crow::Blueprint lessonsBlueprint;
	crow::Blueprint quizBlueprint;
	QuizCreator quizCreator;

	void setupApp();
};