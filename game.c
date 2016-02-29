#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "error.h"
#include "basic.h"
#include "sprite.h"
#include "log.h"
#include "strings.h"
#include "utils.h"
#include "data.h"

int game_loop()
{
	int done = FALSE;
	enum game_state state = PLAYING;

	double clock;		/* last time sample in seconds */
	double render_timer;	/* time control for rendering */
	double frmtime;		/* timer used for when to show updated fps */
	int frms;		/* frame counter for fps display */

	DT = 0.0;
	render_timer = 0.0;
	clock = getseconds();

	if (DEBUG) {
		frmtime = getseconds();
		frms = 0;
	}

	/* everything related to this initializing this sprite
	 * should eventually be abstracted to a function in the
	 * sprite header */
	// struct sprite pl_sprite = SPRITE_DEFAULT;
	// pl_sprite.surface = SDL_LoadBMP(PLAYER_SPR);

	// if (pl_sprite.surface == NULL) {
	// 	throw_err(SDL_BMP_ERR);
	// }

	// pl_sprite.frames = 3;
	// pl_sprite.dest_rect = malloc(sizeof(*(pl_sprite.dest_rect)));
	// pl_sprite.dest_rect->x = 0;
	// pl_sprite.dest_rect->y = 0;
	// pl_sprite.dest_rect->w = 200;
	// pl_sprite.dest_rect->h = 144;

	// pl_sprite.source_rect = malloc(sizeof(*(pl_sprite.source_rect)));
	// *(pl_sprite.source_rect) = *(pl_sprite.dest_rect);

	// anispeed(&pl_sprite, (1/60.0));
	// aniset(&pl_sprite, pl_sprite.frames);
	// anireverse(&pl_sprite, TRUE);
	// anistart(&pl_sprite, TRUE);

	logstr("Entering main game loop");
	/* this stuff is all for testing, any engine-related
	 * code needs to be abstracted out at some point */
	while (!done) {
		DT = getseconds() - clock; /* get the current delta time for this frame */
		clock = getseconds(); /* updates the clock to check the next delta time */

		switch (state) {
		case PLAYING:
			/* checks if the frame is ready to render */
			if (render_timer >= (1/TARGET_FRAME_RATE)) {
				if (DEBUG)
					/* increment counter for framerate */
					frms++;

				drawall();

				SDL_UpdateWindowSurface(WINDOW);

				if (SDL_FillRect(SCREEN, NULL, SDL_MapRGB(
								SCREEN->format,
								255, 255, 255))
						!= 0) {
					throw_err(SDL_RECT_ERR);
				}

				/* do not set to zero, remove the accumulated
				 * frame time to avoid skipping */
				render_timer -= (1/TARGET_FRAME_RATE);
			}

			if (DEBUG) {
				if (frmtime >= 1) {
					char fps[LOG_LINE_SIZE];
					snprintf(fps, LOG_LINE_SIZE,
							"FPS: %d", frms);
					logstr(fps);
					frms = 0;
					/* decrement frmtime instead of setting to 0 */
					frmtime--;
				}
			}

			render_timer += DT;

			if (DEBUG)
				frmtime += DT;

			break;
		case PAUSED:
			break;
		case MAIN_MENU:
			break;
		default:
			throw_err(NO_STATE_ERR);
		}

	}
	logstr("Left main game loop");

	SDL_FreeSurface(OBJECTS[PLYR].spr.surface);
	return 0;
}
