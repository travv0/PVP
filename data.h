/* this file is where stuff like game sprites and objects are set up */
#ifndef __DATA_H
#define __DATA_H

#include "sprite.h"
#include "object.h"

enum sprite_indices {
	PLYR,
	NUMOFSPRITES
};

/* array of all sprites in the game */
extern struct sprite SPRITES[NUMOFSPRITES];

#endif
