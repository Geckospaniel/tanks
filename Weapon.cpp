#include "Weapon.h"
#include "WeaponBasic.h"
#include "WeaponSpread.h"
#include "Renderer.h"

extern float toRadian(float degrees);

Weapon::Weapon(WorldSpace& ws) : ws(ws) 
{
}

void Weapon::drawPath(Level& level, Vector2& position, float tankRotation)
{
	auto getDirection = [&](float rot) -> Vector2
	{
		float tRot = toRadian(rot);
		return Vector2(cos(tRot), sin(tRot));
	};

	Vector2 direction = getDirection(tankRotation);

	Vector2 offset = position;
	Vector2 rayPosition = offset;

	auto update = [&](float r) -> void
	{
		tankRotation = r + (r - tankRotation);
		direction = getDirection(tankRotation);
		
		offset = rayPosition;
	};

	float rLength = maxRange;

	for(float rayI = 0; rayI < rLength; rayI+=0.001f)
	{
		Vector2 last = offset + (direction * (rayI - 0.001f));
		rayPosition = offset + (direction * rayI);

		bool out = !level.isInsideBorders(rayPosition);

		if(out)
		{
			if(!level.insideBordersX(rayPosition[X]))
				update(90);
			if(!level.insideBordersY(rayPosition[Y]))
				update(180);

			rLength = rLength - rayI;
			rayI = 0.0f;
		}
		else if(level.intersects(rayPosition))
		{
			Vector2 lastIndex = last - level.getPosition();
			Vector2 index = rayPosition - level.getPosition();

			size_t x = index[X] / level.tileW();
			size_t y = index[Y] / level.tileH();

			size_t lx = lastIndex[X] / level.tileW();
			size_t ly = lastIndex[Y] / level.tileH();

		//	SDL_Log("%lu %lu : %lu %lu", x, y, lx, ly);
			if(lx != x)
				update(90);
			if(ly != y)
				update(180);

			rLength = rLength - rayI;
			rayI = 0.0f;

		//	level(x, y) = 0;
		}

		if(out)
			Render::setColor(255, 0, 0);
		else
			Render::setColor(0, 255, 0);
		rayPosition = ws.toScreen(rayPosition);
		Render::dot(rayPosition[X], rayPosition[Y]);
	}
}

bool Weapon::isFired()
{
	return fired;
}

Weapon* makeWeapon(WeaponType type, WorldSpace& ws)
{
	Weapon* weapon;

	switch(type)
	{
		case WEAPON_BASIC: weapon = new WeaponBasic(ws); break;
		case WEAPON_SPREAD: weapon = new WeaponSpread(ws, 3); break;
	}

	return weapon;
}
