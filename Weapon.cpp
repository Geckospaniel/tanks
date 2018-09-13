#include "Weapon.h"
#include "WeaponBasic.h"
#include "Renderer.h"

extern float toRadian(float degrees);

Weapon::Weapon() 
{
}

void Weapon::addImmune(size_t id)
{
	immuneTanks.push_back(id);
}

void Weapon::drawPath(WorldSpace& ws, Level& level, Vector2& position, float& tankRotation)
{
	SDL_Log("%.2f : %.2f", position[X], position[Y]);

	auto getDirection = [&](float rot) -> Vector2
	{
		float tRot = toRadian(rot);
		return Vector2(cos(tRot), sin(tRot));
	};

	Vector2 direction = getDirection(tankRotation);

	Vector2 offset = position;
	Vector2 rayPosition = offset;

	for(float rayI = 0; rayI < 0.4f; rayI+=0.001f)
	{
		rayPosition = offset + (direction * rayI);

		if(level.intersects(rayPosition))
		{
			SDL_Log("[%.2f] Hit", rayI);
		}
	}
}

Weapon* makeWeapon(WeaponType type)
{
	Weapon* weapon;

	switch(type)
	{
		case WEAPON_BASIC: weapon = new WeaponBasic(); break;
	}

	return weapon;
}
