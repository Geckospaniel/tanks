#include "WeaponSpread.h"
#include "Renderer.h"

template <typename WeaponClass>
WeaponSpread<WeaponClass>::WeaponSpread(WorldSpace& ws, size_t directions) : Weapon(ws)
{
	this->directions = directions;
	weapons.resize(directions);
}

template <typename WeaponClass>
bool WeaponSpread<WeaponClass>::doesDamage()
{
	return false;
}

template <typename WeaponClass>
void WeaponSpread<WeaponClass>::update(Level& level, const Vector2& tankPosition, const float& tankRotation)
{
}

template <typename WeaponClass>
void WeaponSpread<WeaponClass>::draw()
{
	for(size_t i = 0; i < weapons.size(); i++)
		weapons[i]->draw();
}
