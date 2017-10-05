#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "game.h"
#include "PVPengine/error.h"
#include "PVPengine/basic.h"
#include "PVPengine/sprite.h"
#include "PVPengine/log.h"
#include "PVPengine/str.h"

void game_loop(void)
{
	enum game_state state = PLAYING;

	switch (state) {
		case PLAYING:
			break;
		case PAUSED:
			break;
		case MAIN_MENU:
			break;
		default:
			throw_err(NO_STATE_ERR);
	}
}
