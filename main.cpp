#include <SDL2/SDL.h>

#include "Window.h"
#include "Renderer.h"
#include "Game.h"

int main(int argc, char** argv)
{
	/*	Check whether SDL can be initialized.
	 *	SDL_Init return 0 on success or -1 on failure.
	 */

	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		bool isRunning;
		Window win("", isRunning, true, 4, 2);

		Game game(win);

		while(isRunning)
		{
			// Input

			SDL_Event evnt;
			while(SDL_PollEvent(&evnt))
			{
				win.input(evnt, isRunning);
				game.input(evnt);
			}

			// Update

			game.update();

			// Draw

			Render::setColor(0, 0, 0);
			Render::clearScreen();

			game.draw();

			Render::render();
		}

		SDL_Quit();
	}
	else
		SDL_Log("Unable to initialize : %s!", SDL_GetError());

	return 0;
}
