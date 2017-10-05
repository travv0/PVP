#include <SDL2/SDL.h>

#include "PVPengine/basic.h"
#include "PVPengine/object.h"
#include "PVPengine/recthlpr.h"
#include "data.h"

#define MOVE_SPEED	4

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
		tmp.y -= MOVE_SPEED * DT;
		if (!chkvoob(tmp))
			obj->y -= MOVE_SPEED * DT;
	}
	if (ball.y > obj->y) {
		SDL_Rect tmp = obj->spr.hb_rect;
		tmp.y += MOVE_SPEED * DT;
		if (!chkvoob(tmp))
			obj->y += MOVE_SPEED * DT;
	}

	return 0;
}
