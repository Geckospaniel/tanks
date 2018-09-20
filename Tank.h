#ifndef TANK_H
#define TANK_H

#include "Level.h"
#include "Vector2.h"
#include "WorldSpace.h"
#include "Weapon.h"

class Tank
{
public:
	Tank(WorldSpace& ws, Vector2 pos, Vector2 sz, size_t id);

	void update(Level& level);
	void drawWeapon(Level& level);
	void draw();

private:
	WorldSpace& ws;

	float rotation;

	Vector2 position;
	Vector2 radius;

	size_t id;
	Weapon* weapon;
};

#endif
