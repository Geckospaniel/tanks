#ifndef TANK_H
#define TANK_H

#include "Level.h"
#include "Vector2.h"
#include "WorldSpace.h"
#include "Weapon.h"

#include <SDL2/SDL_events.h>

#include <map>

class Tank
{
public:
	Tank(WorldSpace& ws, Vector2 pos, Vector2 sz, size_t id);

	void update(Level& level);
	void input(SDL_Event evnt);

	void drawWeapon(Level& level);
	void drawHealth();
	void draw();

private:
	WorldSpace& ws;

	float rotation;
	float health;

	Vector2 position;
	Vector2 radius;

	size_t id;
	Weapon* weapon;

	struct Key { bool pressed; float effect; };
	std::map <int, Key> keys;
};

#endif
