#include "TankHandler.h"

#include <SDL2/SDL_log.h>

#include <random>

void TankHandler::add(size_t amount, Level& level, WorldSpace& ws)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution <size_t> xRand(0, level.getTileAmount(X) - 1);
	std::uniform_int_distribution <size_t> yRand(0, level.getTileAmount(Y) - 1);

	float radiusX = 0.025f;
	float radiusY = 0.05f;

	for(size_t i = 0; i < amount; i++)
	{
		size_t x = xRand(gen);
		size_t y = yRand(gen);

		if(level(x, y) == 1)
		{
			i--;
			continue;
		}

		float tw = level.tileW();
		float th = level.tileH();

		Vector2 position = level.getPosition() + Vector2(tw * x, th * y) + (Vector2(tw, th) / 2);
		Vector2 radius(radiusX, radiusY);

		SDL_Log("Created at %.2f %.2f!", position[X], position[Y]);

		tanks.push_back( Tank(ws, position, radius, i) );
	}
}

void TankHandler::update(Level& level)
{
	for(size_t i = 0; i < tanks.size(); i++)
		tanks[i].update(level);
}

void TankHandler::draw(Level& level)
{
	for(size_t i = 0; i < tanks.size(); i++)
	{
		tanks[i].draw();
		tanks[i].drawWeapon(level);
	}
}
