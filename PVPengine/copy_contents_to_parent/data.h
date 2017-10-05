/* this file is where stuff like game sprites and objects are set up */
#ifndef __DATA_H
#define __DATA_H

#include "PVPengine/object.h"

enum sprite_indices {
	SPR_PLAYER,
	NUMOFSPRITES
};

enum object_indices {
	OBJ_DEFAULT,
	OBJ_PLAYER,
	NUMOFOBJECTS
};

/* array of all sprites in the game */
extern struct sprite SPRITES[NUMOFSPRITES];

/* array of all objects in the game */
extern struct object OBJECTS[NUMOFOBJECTS];

#endif
