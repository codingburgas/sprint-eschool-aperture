#pragma once

#include <raylib.h>

#include <utilities.hpp>
#include <string>

class App
{
public:
	App(Vector2 setScreen, std::string setName);
	~App();


public:
	void Run();

private:
	GameState gameState;
	Vector2 screen;
	std::string name;

};