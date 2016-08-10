#include <SDL2/SDL.h>
#include <stdlib.h>

#include "engine/basic.h"
#include "engine/object.h"
#include "engine/log.h"
#include "data.h"
#include "recthlpr.h"
#include "basic.h"
#include "ext.h"

#define MAX_VELOCITY	30
#define BALL_COOLDOWN	60

int ballstep(struct object *obj)
{
	SDL_Rect tmp = obj->spr.hb_rect;
	int totalvel = abs(obj->hvel) + abs(obj->vvel);
	int i;

	if (obj->ext[BALL_EXT_COOLDOWN] > 0) {
		obj->ext[BALL_EXT_COOLDOWN]--;
		return;
	}
	else if (totalvel == 0) {
		obj->hvel = BALL_START_VEL;
		obj->vvel = BALL_START_VEL;
	}

	tmp.x += obj->hvel;
	tmp.y += obj->vvel;

	/* check if intersects with either paddle */
	for (i = 0; i < OBJ_MGR->objcnt; ++i) {
		if ((objmget(OBJ_MGR, i)->type == OBJ_PLAYER ||
					objmget(OBJ_MGR, i)->type == OBJ_ENEMY) &&
				SDL_HasIntersection(&obj->spr.hb_rect,
					&objmget(OBJ_MGR, i)->spr.hb_rect)) {
			obj->hvel = -obj->hvel;
			if (totalvel < MAX_VELOCITY)
				obj->hvel *= 1.1;
		}
	}

	if (chkhoob(tmp)) {
		/* reset position and don't move for a couple seconds */
		obj->x = WIN_WIDTH / 2;
		obj->y = WIN_HEIGHT / 2;
		obj->hvel = 0;
		obj->vvel = 0;
		obj->ext[BALL_EXT_COOLDOWN] = BALL_COOLDOWN;
	}
	if (chkvoob(tmp)) {
		obj->vvel = -obj->vvel;
		if (totalvel < MAX_VELOCITY)
			obj->vvel *= 1.1;
	}

	obj->x += obj->hvel;
	obj->y += obj->vvel;

	obj->spr.dest_rect.x = obj->x;
	obj->spr.dest_rect.y = obj->y;

	return 0;
}
