#include <menu.hpp>

#include <raylib.h>
#include <raygui.h>

#include <utilities.hpp>


GameState menu()
{
	int activeOption;
	Font titleFont = LoadFontEx("styles/Gefika.otf", 230, nullptr, 0);
	Color apertureBlue = { 0, 118, 163, 255 };
    
	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(GetColor(GuiGetStyle(DEFAULT, BASE_COLOR_NORMAL)));

			// Title
			DrawTextEx(titleFont, "Aperture\nNotepad", Vector2{100, 60}, 70, 6, apertureBlue);

			// Menu options
			GuiListView(Rectangle{ 100, 240, 330, 200 }, "Notes;Settings;Quit", nullptr, &activeOption); // Pass null to scroll index since we don't use it

		EndDrawing();

		switch (activeOption)
		{
		case 0: return SELECT_LESSONS;
		case 1: return SETTINGS;
		case 2: return QUIT;
		}
	}

	UnloadFont(titleFont);
	return QUIT;
}