#ifndef WEAPON_BASIC_H
#define WEAPON_BASIC_H

#include "Weapon.h"
#include "Vector2.h"
#include "WorldSpace.h"

class WeaponBasic : public Weapon
{
public:
	WeaponBasic(WorldSpace& ws);

	void update(Level& level, const Vector2& tankPosition, const float& tankRotation);
	void draw();

private:
	Vector2 bulletPosition;
	Vector2 direction;

	float speed;
	float length;
	float rotation;
};

#endif
