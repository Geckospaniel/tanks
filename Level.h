#ifndef LEVEL_H
#define LEVEL_H

#include "WorldSpace.h"
#include "Vector2.h"

#include <vector>

class Level
{
public:
	Level(WorldSpace& ws, Vector2 pos, Vector2 sz, const size_t tx, const size_t ty);

	void draw();

	Vector2& getPosition();
	Vector2& getSize();

	bool isInsideBorders(Vector2 ip);
	bool insideBordersX(float ip);
	bool insideBordersY(float ip);

	bool intersects(Vector2 ip);

	float tileW();
	float tileH();

	char operator()(size_t x, size_t y);
	size_t getTileAmount(int dimension);

private:
	WorldSpace& ws;

	Vector2 position;
	Vector2 size;

	const size_t tilesX;
	const size_t tilesY;

	std::vector <std::vector <char>> data;
};

#endif
