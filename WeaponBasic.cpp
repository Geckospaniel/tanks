#include "WeaponBasic.h"
#include "Renderer.h"

#include <SDL2/SDL_log.h>

extern float toRadian(float);

WeaponBasic::WeaponBasic(WorldSpace& ws) : Weapon(ws)
{
	SDL_Log("Created basic weapon!");

	speed = 0.01f;
	length = 0.0f;

	maxRange = 0.0f;
}

void WeaponBasic::update(Level& level, const Vector2& tankPosition, const float& tankRotation)
{
	if(!fired)
	{
		fired = true;
		bulletPosition = tankPosition;
		rotation = tankRotation;
	}

	auto getDirection = [&](float rot) -> Vector2
	{
		float tRot = toRadian(rot);
		return Vector2(cos(tRot), sin(tRot));
	};

	for(float i = 0.0f; i < speed; i+=0.001f)
	{
		Vector2 direction = getDirection(rotation);
		Vector2 last = bulletPosition = bulletPosition;

		auto update = [&](float r) -> void
		{
			rotation = r + (r - rotation);
			bulletPosition = last;
		};

		length+=0.001f;
		if(0 && length >= maxRange)
		{
			length = 0.0f;
			fired = false;

			return;
		}

		bulletPosition+=(direction * 0.001f);

		bool out = !level.isInsideBorders(bulletPosition);

		if(out)
		{
			if(!level.insideBordersX(bulletPosition[X]))
				update(90);
			if(!level.insideBordersY(bulletPosition[Y]))
				update(180);
		}
		else if(level.intersects(bulletPosition))
		{
			Vector2 lastIndex = last - level.getPosition();
			Vector2 index = bulletPosition - level.getPosition();

			size_t x = index[X] / level.tileW();
			size_t y = index[Y] / level.tileH();

			size_t lx = lastIndex[X] / level.tileW();
			size_t ly = lastIndex[Y] / level.tileH();

			bool sideOccupiedX = (level(x - 1, y + 0) == 1 || level(x + 1, y + 0) == 1);
			bool sideOccupiedY = (level(x + 0, y - 1) == 1 || level(x + 0, y + 1) == 1);

			if(lx != x)// || !sideOccupiedX)
				update(90);
			if(ly != y) //|| !sideOccupiedY)
				update(180);

			bulletPosition = last;

			level(x, y) = 0;
		}
	}
}

void WeaponBasic::draw()
{	
	Render::setColor(255, 255, 255);
	Vector2 p = ws.toScreen(bulletPosition);
	Render::dot(p[X], p[Y]);

	for(int i = 0; i < 360; i++)
	{
		float tRot = toRadian(i);
		Vector2 direction(cos(tRot), sin(tRot));

		Vector2 pos = ws.toScreen( bulletPosition + (direction * 0.02f) );
		Render::dot(pos[X], pos[Y]);
	}
}
