#ifndef __OBJECT_H
#define __OBJECT_H

#include "sprite.h"

struct object {
	struct sprite	spr;
	float		x;
	float		y;
	int		(*step)();
};

#endif
