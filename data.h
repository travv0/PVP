/* this file is where stuff like game sprites and objects are set up */
#ifndef __DATA_H
#define __DATA_H

#include "sprite.h"
#include "object.h"

enum object_indices {
	PLYR,
	NUMOFOBJECTS
};

/* array of all objects in the game */
extern struct object OBJECTS[NUMOFOBJECTS];

#endif
