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

	void drawPath(Level& level, Vector2& position, float tankRotation);

	bool isFired();
	virtual void fire();
	virtual bool doesDamage()=0;

	virtual void update(Level& level, const Vector2& tankPosition, const float& tankRotation)=0;
	virtual void draw()=0;

protected:
	float maxRange;
	bool destructive;
	bool fired;

	WorldSpace& ws;
};

enum WeaponType
{
	WEAPON_BASIC,
	WEAPON_SPREAD
};

Weapon* makeWeapon(WeaponType type, WorldSpace& ws);

#endif
