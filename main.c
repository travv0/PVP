#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "engine/error.h"
#include "engine/game.h"
#include "engine/log.h"
#include "strings.h"
#include "engine/basic.h"
#include "engine/objmanager.h"
#include "engine/pvp.h"
#include "data.h"

#define PADDLE_OFFSET	50

int main(int argc, char *args[])
{
	if (argc >= 2 && (strcmp(args[1], "-d") == 0 ||
				strcmp(args[1], "--debug") == 0))
		DEBUG = TRUE;
	else
		DEBUG = FALSE;

	pvpinit(DEBUG);		/* call at beginning of main function */

	objminit(&OBJ_MGR);
	log("Object manager initialized", "%s");

	objmadd(OBJ_MGR, OBJECTS[OBJ_PLAYER], SPRITES[SPR_PADDLE], 0 + PADDLE_OFFSET, WIN_HEIGHT / 2);
	objmadd(OBJ_MGR, OBJECTS[OBJ_ENEMY], SPRITES[SPR_PADDLE], WIN_WIDTH - PADDLE_OFFSET, WIN_HEIGHT / 2);
	objmadd(OBJ_MGR, OBJECTS[OBJ_BALL], SPRITES[SPR_BALL], WIN_WIDTH / 2, WIN_HEIGHT / 2);
	log("Objects added to object manager", "%s");

	initsprites();
	log("Sprites initialized", "%s");

	/* main game loop */
	game_loop();

	log("Cleaning up", "%s");
	pvpclean();		/* call to clean up memory used by SDL */

	log("Quitting game...", "%s");
	return 0;
}
