#include "Game.h"
#include "Renderer.h"

Game::Game(Window& win) :
	ws(win),
	level(ws, Vector2(-1.0f, -1.0f), Vector2(2.0f, 2.0f), 100, 100)
{
	tankHandler.add(5000, level, ws);

	gameRunning = true;
	gamePaused = false;
}

void Game::input(SDL_Event evnt)
{
	if(evnt.type == SDL_KEYDOWN)
	{
		switch(evnt.key.keysym.sym)
		{
			// Camera controls
			case SDLK_w: ws[Y]-=0.1f; break;
			case SDLK_s: ws[Y]+=0.1f; break;

			case SDLK_a: ws[X]+=0.1f; break;
			case SDLK_d: ws[X]-=0.1f; break;

			case SDLK_RETURN:
				// Swap the state of gamePaused
				gamePaused = !gamePaused;
			break;
		}
	}
}

void Game::update()
{
	// Update if game is running and isn't paused
	if(gameRunning && !gamePaused)
	{
		tankHandler.update(level);
	}
}

void Game::draw()
{
	if(gamePaused)ws.draw();
	level.draw();
	tankHandler.draw(level);

}
