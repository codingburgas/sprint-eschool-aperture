#include <raylib.h>

int main()
{
	InitWindow(1280, 800, "Aperture Pad");

	SetTargetFPS(60);
	
	while (!WindowShouldClose())
	{
		BeginDrawing();

			ClearBackground(BLACK);
		
		EndDrawing();
	}

	CloseWindow();
}