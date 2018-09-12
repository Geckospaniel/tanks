#ifndef TANK_HANDLER_H
#define TANK_HANDLER_H

#include "WorldSpace.h"
#include "Level.h"
#include "Tank.h"

#include <SDL2/SDL_events.h>

#include <vector>

class TankHandler
{
public:
	void add(size_t amount, Level& level, WorldSpace& ws);

	void input(SDL_Event evnt);
	void update(Level& level);
	void draw();

private:
	std::vector <Tank> tanks;
};

#endif
