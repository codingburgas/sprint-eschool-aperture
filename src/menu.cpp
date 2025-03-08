#include <menu.hpp>

#include <raylib.h>
#include <raygui.h>

#include <utilities.hpp>

GameState menu()
{
	int activeOption;
	Font titleFont = LoadFontEx("styles/Gefika.otf", 230, NULL, 0);
	Color apertureBlue = { 0, 118, 163, 255 };

	GuiSetStyle(LISTVIEW, LIST_ITEMS_HEIGHT, 60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL)));

			// Title
			DrawTextEx(titleFont, "Aperture\nNotepad", Vector2{100, 60}, 110, 6, apertureBlue);

			// Menu options
			GuiListView(Rectangle{ 100, 340, 430, 300 }, "Notes;Settings;About us;Quit", NULL, &activeOption); // Pass NULL to scroll index since we don't use it

		EndDrawing();

		switch (activeOption)
		{
		case 0: return SELECT_LESSONS;
		case 1: return SETTINGS;
		case 2: return ABOUT_US;
		case 3: return QUIT;
		}
	}

	UnloadFont(titleFont);
	return QUIT;
}