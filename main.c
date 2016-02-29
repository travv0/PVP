#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "error.h"
#include "game.h"
#include "log.h"
#include "strings.h"
#include "basic.h"

int main(int argc, char *args[])
{
	if (argc >= 2 && (strcmp(args[1], "-d") == 0 ||
				strcmp(args[1], "--debug") == 0)) {
		DEBUG = TRUE;
		clearfile(LOG_FILE);
		logstr("Debugging enabled");
	} else
		DEBUG = FALSE;

	int errcode;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
		throw_err(SDL_INIT_ERR);
	}
	logstr("SDL initialized");

	WINDOW = SDL_CreateWindow("PVP", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	if (WINDOW == NULL) {
		throw_err(SDL_WIND_ERR);
	}
	logstr("Main WINDOW created");

	RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);

	if (RENDERER == NULL) {
		throw_err(SDL_REND_ERR);
	}
	logstr("Renderer created");

	SCREEN = SDL_GetWindowSurface(WINDOW);

	if (SCREEN == NULL) {
		throw_err(SDL_SURF_ERR);
	}
	logstr("Main surface created");

	if (SDL_FillRect(SCREEN, NULL, SDL_MapRGB(SCREEN->format, 255, 255, 255)) != 0) {
		throw_err(SDL_RECT_ERR);
	}
	SDL_UpdateWindowSurface(WINDOW);

	EVENT = malloc(sizeof(*EVENT));

	initsprites();
	logstr("Sprites initialized");

	/* main game loop */
	errcode = game_loop();

	logstr("Cleaning up");
	free(EVENT);
	unloadsprites();
	SDL_DestroyWindow(WINDOW);
	SDL_Quit();

	logstr("Quitting game...");
	return errcode;
}
