#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "game.h"
#include "engine/error.h"
#include "engine/basic.h"
#include "engine/sprite.h"
#include "engine/log.h"
#include "engine/str.h"
#include "basic.h"

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
