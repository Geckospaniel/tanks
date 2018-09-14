#ifndef WEAPON_BASIC_H
#define WEAPON_BASIC_H

#include "Weapon.h"
#include "Vector2.h"
#include "WorldSpace.h"

class WeaponBasic : public Weapon
{
public:
	WeaponBasic(WorldSpace& ws);

private:
	float speed;
};

#endif
