#include <stdio.h>
#include "sdl.h"

#include "error.h"
#include "game.h"
#include "log.h"

int main(int argc, char *args[])
{
	clearfile("log.txt");

	logstr("this is a test");
	logstr("this is another test");
	return throw_err(SDL_INIT_ERR);

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *screen = NULL;

	int errcode;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
		return throw_err(SDL_INIT_ERR);
	}

	window = SDL_CreateWindow("AcAdvGame", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	if (window == NULL) {
		return throw_err(SDL_WIND_ERR);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		return throw_err(SDL_REND_ERR);
	}

	screen = SDL_GetWindowSurface(window);

	if (screen == NULL) {
		return throw_err(SDL_SURF_ERR);
	}

	if (SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255)) != 0) {
		return throw_err(SDL_RECT_ERR);
	}
	SDL_UpdateWindowSurface(window);

	/* main game loop */
	errcode = game_loop(window, renderer, screen);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return errcode;
}
