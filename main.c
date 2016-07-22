#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "error.h"
#include "game.h"
#include "log.h"
#include "strings.h"
#include "basic.h"
#include "objmanager.h"
#include "data.h"

int main(int argc, char *args[])
{
	if (argc >= 2 && (strcmp(args[1], "-d") == 0 ||
				strcmp(args[1], "--debug") == 0)) {
		DEBUG = TRUE;
		clearfile(LOG_FILE);
		log("Debugging enabled", "%s");
	} else
		DEBUG = FALSE;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
		throw_err(SDL_INIT_ERR);
	}
	log("SDL initialized", "%s");

	WINDOW = SDL_CreateWindow("PVP", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	if (WINDOW == NULL) {
		throw_err(SDL_WIND_ERR);
	}
	log("Main window created", "%s");

	RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);

	if (RENDERER == NULL) {
		throw_err(SDL_REND_ERR);
	}
	log("Renderer created", "%s");

	SCREEN = SDL_GetWindowSurface(WINDOW);

	if (SCREEN == NULL) {
		throw_err(SDL_SURF_ERR);
	}
	log("Main surface created", "%s");

	if (SDL_FillRect(SCREEN, NULL, SDL_MapRGB(SCREEN->format, 255, 255, 255)) != 0) {
		throw_err(SDL_RECT_ERR);
	}

	EVENT = malloc(sizeof(*EVENT));

	objminit(&OBJ_MGR);
	log("Object manager initialized", "%s");

	objmadd(OBJ_MGR, OBJECTS[OBJ_PLAYER], 0, 0);
	objmadd(OBJ_MGR, OBJECTS[OBJ_PLAYER], 200, 200);
	objmadd(OBJ_MGR, OBJECTS[OBJ_DEFAULT], 0, 200);
	log("Objects added to object manager", "%s");

	initsprites();
	log("Sprites initialized", "%s");

	/* main game loop */
	game_loop();

	log("Cleaning up", "%s");
	objmfree(OBJ_MGR);
	free(EVENT);
	unloadsprites();
	SDL_DestroyWindow(WINDOW);
	SDL_Quit();

	log("Quitting game...", "%s");
	return 0;
}
