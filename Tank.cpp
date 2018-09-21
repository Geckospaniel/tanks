#include "Tank.h"
#include "Renderer.h"

#include <math.h>
#include <random>

float toRadian(float degrees)
{
	return degrees * 0.0174532925;
}

constexpr int preset[4][5]
{
	{ SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN, SDLK_RCTRL },
	{  },
	{  },
	{  }
};

Tank::Tank(WorldSpace& ws, Vector2 pos, Vector2 sz, size_t id) : ws(ws)
{
	position = pos;
	position = Vector2(0.0f, 0.0f);
	radius = sz;

	this->id = id;
	rotation = 0.0f;

	health = 100.0f;

	weapon = makeWeapon(WEAPON_SPREAD, ws);
	SDL_Log("TNK : %p", &position);

	#define K(i) keys[preset[id][i]]

	K(0).effect = -3.5f;
	K(1).effect = +3.5f;

	K(2).effect = +0.003f;
	K(3).effect = -0.003f;

	K(4).effect;
}

void Tank::update(Level& level)
{
	float tRot = toRadian(rotation);
	Vector2 direction(cos(tRot), sin(tRot));

	for(const auto& it : keys)
	{
		if(it.second.pressed)
		{
			if(it.first == preset[id][0] || it.first == preset[id][1])
				rotation+=it.second.effect;

			else if(it.first == preset[id][2] || it.first == preset[id][3])
			{
				Vector2 last = position;
				position+=(direction * it.second.effect);

				if(level.intersects(position))
					position = last;
			}
			
			else if(it.first == preset[id][4])
				weapon->fire();
		}
	}

	if(health > 0)
		health-=0.25f;

	Vector2 cannonEnd = position + (direction * radius[H]);
	weapon->update(level, cannonEnd, rotation);
}

void Tank::input(SDL_Event evnt)
{
	bool pressed;

	switch(evnt.type)
	{
		case SDL_KEYDOWN: pressed = true; break;
		case SDL_KEYUP: pressed = false; break;

		default: return;
	}

	int keyID = evnt.key.keysym.sym;
	if(keys.find(keyID) != keys.end())
		keys[keyID].pressed = pressed;
}

void Tank::drawWeapon(Level& level)
{
	weapon->draw();
	weapon->drawPath(level, position, rotation);
}

void Tank::drawHealth()
{
	Vector2 barPosition = position - (radius * 2);
	Vector2 barSize(radius[Y] * 2, radius[X]);

	float per = barSize[X] / 100;
	Vector2 greenSize(barSize[W] - (per * (100 - health)), barSize[H]);

	Render::setColor(255, 0, 0);
	Render::rect( ws.rectToScreen(barPosition, barSize) );
	
	Render::setColor(0, 255, 0);
	Render::rect( ws.rectToScreen(barPosition, greenSize) );
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
