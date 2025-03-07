#include <app.hpp>
#include <utilities.hpp>
#include <raylib.h>
#include <main_menu.hpp>
#include <about_us.hpp>
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
			gameState = select_lessons();
			break;
		case EDIT_LESSONS:
			gameState = edit_lessons();
		case ABOUT_US:
			gameState = about();
			break;
		case SETTINGS:
			gameState = settings();
			break;
		}
	}
}