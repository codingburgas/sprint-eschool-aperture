#include <raylib.h>
#include <app.hpp>
#include <utilities.hpp>

int main()
{
	App* app = new App({ 1440, 800 }, "Aperture Notepad");
	app->Run();

	delete app;
}