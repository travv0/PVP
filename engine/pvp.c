#include <stdio.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "error.h"
/* #include "game.h" */
#include "log.h"
#include "str.h"
#include "basic.h"
#include "objmanager.h"

int pvpinit(int debug)
{
	int imgflags;

	srand(time(NULL));

	if (debug == TRUE) {
		DEBUG = TRUE;
		clearfile(LOG_FILE);
		log("Debugging enabled", "%s");
	} else
		DEBUG = FALSE;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
		throw_err(SDL_INIT_ERR);
	}
	log("SDL initialized", "%s");

	//Set texture filtering to linear
	if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		log("Warning: Linear texture filtering not enabled!", "%s");
	}

	WINDOW = SDL_CreateWindow("PVP", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, 0);

	if (WINDOW == NULL) {
		throw_err(SDL_WIND_ERR);
	}
	log("Main window created", "%s");

	RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED);

	if (RENDERER == NULL) {
		throw_err(SDL_REND_ERR);
	}
	log("Renderer created", "%s");

	SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, 0);

	imgflags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgflags) & imgflags)) {
		throw_err(SDL_IMG_INIT_ERR);
	}

	SCREEN = SDL_GetWindowSurface(WINDOW);

	if (SCREEN == NULL) {
		throw_err(SDL_SURF_ERR);
	}
	log("Main surface created", "%s");

	if (SDL_FillRect(SCREEN, NULL, SDL_MapRGB(SCREEN->format, 255, 255, 255)) != 0) {
		throw_err(SDL_RECT_ERR);
	}

	EVENT = malloc(sizeof(*EVENT));

	return 0;
}


int pvpclean()
{
	objmfree(OBJ_MGR);
	free(EVENT);
	unloadsprites();
	SDL_DestroyWindow(WINDOW);
	SDL_Quit();

	return 0;
}
