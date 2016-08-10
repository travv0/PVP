#include <SDL2/SDL.h>
#include <stdlib.h>

#include "engine/basic.h"
#include "engine/object.h"
#include "engine/log.h"
#include "data.h"
#include "recthlpr.h"

#define MAX_VELOCITY 30

int ballstep(struct object *obj)
{
	SDL_Rect tmp = obj->spr.hb_rect;
	int totalvel = abs(obj->hvel) + abs(obj->vvel);

	tmp.x += obj->hvel;
	tmp.y += obj->vvel;

	if (chkhoob(tmp)) {
		obj->hvel = -obj->hvel;
		if (totalvel < MAX_VELOCITY)
			obj->hvel *= 1.1;
	}
	if (chkvoob(tmp)) {
		obj->vvel = -obj->vvel;
		if (totalvel < MAX_VELOCITY)
			obj->vvel *= 1.1;
	}

	log(totalvel, "Total velocity: %d");
	obj->x += obj->hvel;
	obj->y += obj->vvel;

	obj->spr.dest_rect.x = obj->x;
	obj->spr.dest_rect.y = obj->y;
}
