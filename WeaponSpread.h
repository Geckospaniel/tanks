#ifndef WEAPON_SPREAD_H
#define WEAPON_SPREAD_H

#include "Weapon.h"
#include "Level.h"
#include "WorldSpace.h"

#include <vector>

template <typename WeaponClass>
class WeaponSpread : public Weapon
{
public:
	WeaponSpread(WorldSpace& ws, size_t directions);

	bool doesDamage();
	void update(Level& level, const Vector2& tankPosition, const float& tankRotation);
	void draw();

private:
	std::vector <Weapon*> weapons;

	size_t directions;
};

#endif
