#include "WeaponSpread.h"
#include "Renderer.h"

WeaponSpread::WeaponSpread(WorldSpace& ws, size_t directions) : Weapon(ws)
{
	this->directions = directions;
	weapons.resize(directions);

	type = WEAPON_BASIC;

	for(size_t i = 0; i < directions; i++)
		weapons[i] = makeWeapon(WEAPON_BASIC, ws);
}

bool WeaponSpread::doesDamage()
{
	return false;
}

void WeaponSpread::update(Level& level, const Vector2& tankPosition, const float& tankRotation)
{
	for(size_t i = 0; i < weapons.size(); i++)
		weapons[i]->update(level, tankPosition, tankRotation);
}

void WeaponSpread::draw()
{
	for(size_t i = 0; i < weapons.size(); i++)
		weapons[i]->draw();
}
