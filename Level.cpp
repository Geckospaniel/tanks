#include "Level.h"
#include "Renderer.h"

Level::Level(WorldSpace& ws, Vector2 pos, Vector2 sz, const size_t tx, const size_t ty) : ws(ws), tilesX(tx), tilesY(ty)
{
	position = pos;
	size = sz;

	data.resize(tilesX, std::vector <char> (tilesY, 0));
}

void Level::draw()
{
	auto extendedRect = [&](const Vector2& p, const Vector2& s) -> SDL_Rect
	{
		SDL_Rect r = ws.rectToScreen(p, s);
		r.w++;
		r.h++;

		return r;
	};

	Render::setColor(100, 100, 100);

	float tileW = size[W] / tilesX;
	float tileH = size[H] / tilesY;

	for(size_t x = 0; x < tilesX; x++)
	{
		for(size_t y = 0; y < tilesY; y++)
		{
			if(data[x][y] == 1)
			{
				Vector2 pos = position + Vector2(tileW * x, tileH * y);
				Vector2 tileSize(tileW, tileH);

				Render::rect(extendedRect(pos, tileSize));
			}
		}
	}

	Render::setColor(255, 255, 255);
	Render::rectLines( extendedRect(position, size) );	
}

Vector2& Level::getPosition()
{
	return position;
}

Vector2& Level::getSize()
{
	return size;
}

float Level::tileW()
{
	return size[W] / tilesX;
}

float Level::tileH()
{
	return size[H] / tilesY;
}

char& Level::operator()(size_t x, size_t y)
{
	return data[x][y];
}

size_t Level::getTileAmount(int dimension)
{
	switch(dimension)
	{
		case X: return tilesX;
		case Y: return tilesY;

		default: return 0;
	}
}
