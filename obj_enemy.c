#include <SDL2/SDL.h>

#include "engine/basic.h"
#include "engine/object.h"
#include "data.h"
#include "recthlpr.h"

#define MOVE_SPEED	8

int enemystep(struct object *obj)
{
	struct object ball;
	unsigned int i;

	/* get ball object */
	for (i = 0; i < OBJ_MGR->objcnt; ++i) {
		if (objmget(OBJ_MGR, i)->type == OBJ_BALL)
			ball = *objmget(OBJ_MGR, i);
	}

	if (ball.y < obj->y) {
		SDL_Rect tmp = obj->spr.hb_rect;
		tmp.y -= MOVE_SPEED;
		if (!chkvoob(tmp))
			obj->y -= MOVE_SPEED;
	}
	if (ball.y > obj->y) {
		SDL_Rect tmp = obj->spr.hb_rect;
		tmp.y += MOVE_SPEED;
		if (!chkvoob(tmp))
			obj->y += MOVE_SPEED;
	}

	obj->spr.dest_rect.x = obj->x;
	obj->spr.dest_rect.y = obj->y;

	return 0;
}
