/* this file is where stuff like game sprites and objects are set up */
#ifndef __DATA_H
#define __DATA_H

#include "object.h"

enum object_indices {
	OBJ_PLAYER,
	OBJ_DEFAULT,
	NUMOFOBJECTS
};

/* array of all objects in the game */
extern struct object OBJECTS[NUMOFOBJECTS];

#endif
