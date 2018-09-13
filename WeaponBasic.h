#ifndef WEAPON_BASIC_H
#define WEAPON_BASIC_H

#include "Weapon.h"
#include "Vector2.h"

class WeaponBasic : public Weapon
{
public:
	WeaponBasic();

private:
	float speed;
};

#endif
