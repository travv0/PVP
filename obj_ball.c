#include <SDL2/SDL.h>
#include <stdlib.h>

#include "engine/basic.h"
#include "engine/object.h"
#include "engine/log.h"
#include "data.h"
#include "recthlpr.h"
#include "basic.h"
#include "ext.h"

#define BALL_MAX_VELOCITY	30
#define BALL_VEL_INC_RATE	1.1
#define BALL_ANGLE_MODIFIER	4

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

			/* change vertical velocity based on where it hit paddle */
			obj->vvel -= (objmget(OBJ_MGR, i)->y - obj->y) /
				BALL_ANGLE_MODIFIER;

			/* reverse direction */
			obj->hvel = -obj->hvel;

			/* increase horizontal velocity if it's not maxed out */
			if (totalvel < BALL_MAX_VELOCITY)
				obj->hvel *= BALL_VEL_INC_RATE;

			/* if inside of the paddle, get out of there! */
			if (objmget(OBJ_MGR, i)->type == OBJ_PLAYER) {
				while (SDL_HasIntersection(&obj->spr.hb_rect,
							&objmget(OBJ_MGR, i)->spr.hb_rect)) {
					obj->x++;
					obj->spr.hb_rect.x++;
				}
			} else {
				while (SDL_HasIntersection(&obj->spr.hb_rect,
							&objmget(OBJ_MGR, i)->spr.hb_rect)) {
					obj->x--;
					obj->spr.hb_rect.x--;
				}
			}
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
	if (chkvoob(tmp))
		obj->vvel = -obj->vvel;

	obj->x += obj->hvel;
	obj->y += obj->vvel;

	obj->spr.dest_rect.x = obj->x;
	obj->spr.dest_rect.y = obj->y;

	return 0;
}
