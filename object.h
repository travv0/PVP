/* this file is where game object code goes.
 * a game object is a collection of a sprite, pos, etc., and also
 * a pointer to its step() function which will run every frame (at least) */
#ifndef __OBJECT_H
#define __OBJECT_H

#include "sprite.h"

struct object {
	struct sprite	spr;
	float		x;
	float		y;
	int		(*step)(struct object *obj);
};

/* loop through every sprite and draw it */
void drawall();

/* loop through every object and run it's step function */
void updateall();

/* initialize all objects */
void initobjects();

#endif
