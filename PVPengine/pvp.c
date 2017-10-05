#include <stdio.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "error.h"
#include "log.h"
#include "str.h"
#include "basic.h"
#include "objmanager.h"
#include "utils.h"
#include "../game.h"	/* needed to call user code in game loop */
#include "../basic.h"	/* needed to get user-set framerate and window size */

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

	/* set texture filtering to linear */
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

	TEXTURE = SDL_CreateTexture(RENDERER, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT);

	if (TEXTURE == NULL) {
		throw_err(SDL_TEXTURE_ERR);
	}

	log("Main texture created", "%s");

	if (TTF_Init() == -1)
		throw_err(SDL_TTF_INIT_ERR);

	EVENT = malloc(sizeof(*EVENT));

	return 0;
}

int pvpgameloop(void)
{
	int done = FALSE;

	double clock, prev_clock;	/* last time sample in seconds */
	double frmtime;			/* timer used for when to show updated fps */
	int frms;			/* frame counter for fps display */
	double render_timer;

	render_timer = 0.0;
	prev_clock = getticks();

	if (DEBUG) {
		frmtime = getticks();
		frms = 0;
	}

	log("Entering main game loop", "%s");

	while (!done) {
		clock = getticks();		/* updates the clock to check the next delta time */
		DT = clock - prev_clock;	/* get the current delta time for this frame */

		/* call game loop function that contains user code */
		game_loop();
		updateall();

		/* checks if the frame is ready to render */
		if (render_timer >= (1/TARGET_FRAME_RATE)) {
			if (DEBUG)
				/* increment counter for framerate */
				frms++;

			drawall();

			/* do not set to zero, remove the accumulated
			 * frame time to avoid skipping */
			render_timer -= (1/TARGET_FRAME_RATE);
		}

		if (DEBUG) {
			if (frmtime >= 1) {
				log((uintptr_t) frms, "FPS: %d");
				frms = 0;
				/* decrement frmtime instead of setting to 0 */
				frmtime--;
			}
		}

		render_timer += DT * CUSTOM_TICK_MODIFIER;

		if (DEBUG)
			frmtime += DT * CUSTOM_TICK_MODIFIER;

		prev_clock = clock;
	}
	log("Left main game loop", "%s");

	return 1;
}

int pvpclean()
{
	objmfree(OBJ_MGR);
	free(EVENT);
	unloadsprites();
	SDL_DestroyWindow(WINDOW);
	SDL_DestroyTexture(TEXTURE);
	SDL_Quit();

	return 0;
}
