#ifndef WEAPON_H
#define WEAPON_H

#include "WorldSpace.h"
#include "Vector2.h"
#include "Level.h"

#include <vector>

class Weapon
{
public:
	Weapon();

	void addImmune(size_t id);
	void drawPath(WorldSpace& ws, Level& level, Vector2& position, float& tankRotation);

protected:
	std::vector <size_t> immuneTanks;
};

enum WeaponType
{
	WEAPON_BASIC
};

Weapon* makeWeapon(WeaponType type);

#endif
