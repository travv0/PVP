#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "error.h"
#include "basic.h"
#include "sprite.h"
#include "log.h"
#include "strings.h"
#include "utils.h"

void game_loop(void)
{
	int done = FALSE;
	enum game_state state = PLAYING;

	double clock;		/* last time sample in seconds */
	double frmtime;		/* timer used for when to show updated fps */
	int frms;		/* frame counter for fps display */
	double render_timer;

	DT = 0.0;
	render_timer = 0.0;
	clock = getseconds();

	if (DEBUG) {
		frmtime = getseconds();
		frms = 0;
	}

	log("Entering main game loop", "%s");
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

				updateall();
				drawall();

				/* do not set to zero, remove the accumulated
				 * frame time to avoid skipping */
				render_timer -= (1/TARGET_FRAME_RATE);
			}

			if (DEBUG) {
				if (frmtime >= 1) {
					log(frms, "FPS: %d");
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
	log("Left main game loop", "%s");
}
