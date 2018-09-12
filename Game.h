#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "WorldSpace.h"
#include "Vector2.h"
#include "Level.h"
#include "TankHandler.h"

#include <SDL2/SDL.h>

class Game
{
public:
	Game(Window& win);

	void input(SDL_Event evnt);
	void update();
	void draw();

private:
	WorldSpace ws;

	Level level;
	TankHandler tankHandler;

	bool gamePaused;
	bool gameRunning;
};

#endif
