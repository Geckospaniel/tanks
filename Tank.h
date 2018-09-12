#ifndef TANK_H
#define TANK_H

#include "Level.h"
#include "Vector2.h"
#include "WorldSpace.h"

class Tank
{
public:
	Tank(WorldSpace& ws, Vector2 pos, Vector2 sz);

	void update(Level& level);
	void draw();

private:
	WorldSpace& ws;

	float rotation;

	Vector2 position;
	Vector2 radius;
};

#endif
