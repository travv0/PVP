#include <SDL2/SDL.h>

#include "engine/basic.h"
#include "engine/object.h"
#include "data.h"
#include "recthlpr.h"

#define MOVE_SPEED	2

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

	return 0;
}
