#include "WeaponSpread.h"
#include "Renderer.h"

#include <SDL2/SDL_log.h>

WeaponSpread::WeaponSpread(WorldSpace& ws, size_t directions) : Weapon(ws)
{
	if(directions % 2 == 0)
	{
		SDL_Log("[IT'S A FEATURE] directions is even! Lowering by 1!, %lu -> %lu", directions, directions - 1);
		directions--;
	}

	type = WEAPON_BASIC;

	this->directions = directions;
	weapons.resize(directions);

	for(size_t i = 0; i < directions; i++)
		weapons[i] = makeWeapon(WEAPON_BASIC, ws);
}

bool WeaponSpread::doesDamage()
{
	return false;
}

void WeaponSpread::update(Level& level, const Vector2& tankPosition, const float& tankRotation)
{
	float angle = 45;

	float first = tankRotation - angle;
	float increment = angle / ((directions - 1) / 2);

	for(size_t i = 0; i < weapons.size(); i++)
	{
		float newRotation = first + (increment * i);
		weapons[i]->update(level, tankPosition, newRotation);
	}
}

void WeaponSpread::draw()
{
	for(size_t i = 0; i < weapons.size(); i++)
		weapons[i]->draw();
}
