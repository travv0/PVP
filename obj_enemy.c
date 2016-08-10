#include <SDL2/SDL.h>

#include "engine/basic.h"
#include "engine/object.h"
#include "data.h"

#define MOVE_SPEED	4

int enemystep(struct object *obj)
{
	/* if (mup == TRUE) */
	/* 	obj->y -= MOVE_SPEED; */
	/* if (mdown == TRUE) */
	/* 	obj->y += MOVE_SPEED; */

	obj->spr.dest_rect.x = obj->x;
	obj->spr.dest_rect.y = obj->y;
}
