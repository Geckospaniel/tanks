#ifndef WEAPON_H
#define WEAPON_H

#include "WorldSpace.h"
#include "Vector2.h"
#include "Level.h"

#include <vector>

class Weapon
{
public:
	Weapon(WorldSpace& ws);

	void addImmune(size_t id);
	void drawPath(Level& level, Vector2& position, float tankRotation);

	void update(Vector2& tankPosition, float tankRotation);

protected:
	std::vector <size_t> immuneTanks;

	WorldSpace& ws;
};

enum WeaponType
{
	WEAPON_BASIC
};

Weapon* makeWeapon(WeaponType type, WorldSpace& ws);

#endif
