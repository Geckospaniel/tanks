#include "Tank.h"
#include "Renderer.h"

#include <math.h>

float toRadian(float degrees)
{
	return degrees * 0.0174532925;
}

Tank::Tank(WorldSpace& ws, Vector2 pos, Vector2 sz, size_t id) : ws(ws)
{
	position = pos;
	radius = sz;

	this->id = id;
	rotation = 0.0f;

	weapon = makeWeapon(WEAPON_BASIC);
	SDL_Log("TNK : %p", &position);
}

void Tank::update(Level& level)
{
	rotation+=1.0f;

	Vector2 last = position;

	float tRot = toRadian(rotation);
	Vector2 direction(cos(tRot), sin(tRot));

	position+=(direction * 0.01f);

	if(level.intersects(position))
	{
		position = last;
	}
}

void Tank::drawWeapon(Level& level)
{
	weapon->drawPath(ws, level, position, rotation);
}

void Tank::draw()
{
	float tRot = toRadian(rotation);

	Vector2 vertical(cos(tRot), sin(tRot)),
			horizontal(sin(-tRot), cos(-tRot));

	Vector2 topLeft = ws.toScreen(position - (horizontal * radius[W]) + (vertical * radius[H]));
	Vector2 topRight = ws.toScreen(position + (horizontal * radius[W]) + (vertical * radius[H]));

	Vector2 bottomLeft = ws.toScreen(position - (horizontal * radius[W]) - (vertical * radius[H]));
	Vector2 bottomRight = ws.toScreen(position + (horizontal * radius[W]) - (vertical * radius[H]));

	Render::setColor(255, 0, 0);

	Render::line(topLeft[X], topLeft[Y], topRight[X], topRight[Y]);
	Render::line(topRight[X], topRight[Y], bottomRight[X], bottomRight[Y]);
	Render::line(bottomRight[X], bottomRight[Y], bottomLeft[X], bottomLeft[Y]);
	Render::line(bottomLeft[X], bottomLeft[Y], topLeft[X], topLeft[Y]);

	Vector2 dir = ws.toScreen( position + (vertical * radius[H]) );
	Vector2 tPos = ws.toScreen(position);

	Render::setColor(0, 255, 0);
	Render::line(tPos[X], tPos[Y], dir[X], dir[Y]);
}
