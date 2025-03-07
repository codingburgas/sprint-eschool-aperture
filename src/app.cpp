#include <app.hpp>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <about_us.hpp>
#include <edit_lessons.hpp>
#include <menu.hpp>
#include <select_lessons.hpp>
#include <settings.hpp>
#include <utilities.hpp>

App::App(Vector2 screenDimensions, char windowName[])
	: screen(screenDimensions), gameState(MENU)
{
	InitWindow((int)screen.x, (int)screen.y, windowName);
	SetTargetFPS(60);
	InitAudioDevice();
	GuiLoadStyle("styles/sourceaurelius.rgs");
}

App::~App() {}

void App::Run()
{
	while (gameState != NIL && !WindowShouldClose())
	{
		switch (gameState)
		{
		case MENU:
			gameState = menu();
			break;
		case SELECT_LESSONS:
			gameState = selectLessons();
			break;
		case EDIT_LESSONS:
			gameState = editLessons();
			break;
		case ABOUT_US:
			gameState = about();
			break;
		case SETTINGS:
			gameState = settings();
			break;
		}
	}
}