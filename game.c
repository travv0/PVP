#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "game.h"
#include "PVPengine/error.h"
#include "PVPengine/basic.h"
#include "PVPengine/sprite.h"
#include "PVPengine/log.h"
#include "PVPengine/str.h"
#include "basic.h"
#include "data.h"

#define PADDLE_OFFSET	50

void game_loop(void)
{
	static int startup = TRUE;
	enum game_state state = PLAYING;

	switch (state) {
		case PLAYING:
			if (startup) {
				objmadd(OBJ_MGR, OBJECTS[OBJ_PLAYER], &SPRITES[SPR_PADDLE],
						0 + PADDLE_OFFSET, WIN_HEIGHT / 2);
				objmadd(OBJ_MGR, OBJECTS[OBJ_ENEMY], &SPRITES[SPR_PADDLE],
						WIN_WIDTH - PADDLE_OFFSET, WIN_HEIGHT / 2);
				objmadd(OBJ_MGR, OBJECTS[OBJ_BALL], &SPRITES[SPR_BALL], WIN_WIDTH / 2,
						WIN_HEIGHT / 2);
				objmadd(OBJ_MGR, OBJECTS[OBJ_SCORES], NULL, 0, 0);
				log("Objects added to object manager", "%s");

				initsprites();
				log("Sprites initialized", "%s");

				startup = FALSE;
			}

			break;
		case PAUSED:
			break;
		case MAIN_MENU:
			break;
		default:
			throw_err(NO_STATE_ERR);
	}
}
