#pragma once

#include <utilities.hpp>
#include <raylib.h>
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