#include <stdio.h>
#include <string.h>
#include "sdl.h"

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
		log("Debugging enabled", "%s");
	} else
		DEBUG = FALSE;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Surface *screen = NULL;

	int errcode;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
		throw_err(SDL_INIT_ERR);
	}
	log("SDL initialized", "%s");

	window = SDL_CreateWindow("PVP", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	if (window == NULL) {
		throw_err(SDL_WIND_ERR);
	}
	log("Main window created", "%s");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		throw_err(SDL_REND_ERR);
	}
	log("Renderer created", "%s");

	screen = SDL_GetWindowSurface(window);

	if (screen == NULL) {
		throw_err(SDL_SURF_ERR);
	}
	log("Main surface created", "%s");

	if (SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255)) != 0) {
		throw_err(SDL_RECT_ERR);
	}
	SDL_UpdateWindowSurface(window);

	/* main game loop */
	errcode = game_loop(window, renderer, screen);

	log("Cleaning up", "%s");
	SDL_DestroyWindow(window);
	SDL_Quit();

	log("Quitting game...", "%s");
	return errcode;
}
