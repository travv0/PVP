#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

#include "PVPengine/error.h"
#include "PVPengine/log.h"
#include "strings.h"
#include "PVPengine/basic.h"
#include "PVPengine/objmanager.h"
#include "PVPengine/pvp.h"
#include "game.h"
#include "data.h"
#include "basic.h"
#include "PVPengine/basic.h"

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

	/* main game loop */
	pvpgameloop();

	log("Cleaning up", "%s");
	pvpclean();		/* call to clean up memory used by SDL */

	log("Quitting game...", "%s");
	return 0;
}
