#include <app.hpp>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <about_us.hpp>
#include <utilities.hpp>
#include <main_menu.hpp>
#include <settings_menu.hpp>
#include <edit_lessons_menu.hpp>
#include <select_lessons_menu.hpp>


App::App(Vector2 setScreen, std::string setName)
	: screen(setScreen), name(setName), gameState(MENU)
{
	InitWindow((int)screen.x, (int)screen.y, name.c_str());
	SetTargetFPS(60);
	InitAudioDevice();

}
App::~App() {}

void App::Run()
{
	while (gameState != NIL)
	{
		switch (gameState)
		{
		case MENU:
			gameState = menu();
			break;
		case LESSONS_SELECT:
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