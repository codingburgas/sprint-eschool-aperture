#include <about_us.hpp>

#include <raylib.h>
#include <raygui.h>

#include <utilities.hpp>


GameState aboutUs()
{
	int activeOption;
	Font titleFont = LoadFontEx("styles/Gefika.otf", 230, NULL, 0);
	Color apertureBlue = { 0, 118, 163, 255 };
	Color apertureOrange = { 248, 108, 61, 255 };

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL)));

			// Title
			DrawTextEx(titleFont, "About us\n[:", Vector2{100, 60}, 110, 6, apertureBlue);

			GuiListView(Rectangle{ 100, 340, 430, 300 }, "Go Back;Quit", NULL, &activeOption); // Pass NULL to scroll index since we don't use it

			DrawTextEx(GuiGetFont(), "Our idea:\nAperture Notes is an interactive notepad designed to transform traditional note-taking\ninto a more engaging and effective learning experience.\nWith Aperture Notes, users can write notes, embed videos, and add images\nto better understand topics and overcome the monotony of studying.\nThis innovative approach makes learning more dynamic, personalized, and efficient.", Vector2{30, 490}, 30, 6, apertureOrange);

		EndDrawing();

		switch (activeOption)
		{
		case 0: return MENU;
		case 1: return QUIT;
		}
	}

	UnloadFont(titleFont);
	return QUIT;
}