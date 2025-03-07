#pragma once

#include <raylib.h>

#include <utilities.hpp>

class App
{
public:
	App(Vector2 screenDimensions, char windowName[]);
	~App();

	void Run();

private:
	GameState gameState;
	Vector2 screen;
};