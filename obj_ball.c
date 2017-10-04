#include <SDL2/SDL.h>
#include <stdlib.h>

#include "engine/basic.h"
#include "engine/object.h"
#include "engine/log.h"
#include "data.h"
#include "recthlpr.h"
#include "basic.h"
#include "ext.h"

#define BALL_MAX_VELOCITY	5
#define BALL_VEL_INC_RATE	1.02
#define BALL_ANGLE_MODIFIER	50	// the lower the number, the crazier

int ballstep(struct object *obj)
{
	SDL_Rect tmp = obj->spr.hb_rect;
	int totalvel = abs(obj->hvel) + abs(obj->vvel);
	int i;
	static struct object *player, *enemy;
	struct object *collobj = NULL;

	/* get player and enemy objects */
	if (!player)
		for (i = 0; i < OBJ_MGR->objcnt,
				(player = objmget(OBJ_MGR, i))->type != OBJ_PLAYER; ++i)
			;
	if (!enemy)
		for (i = 0; i < OBJ_MGR->objcnt,
				(enemy = objmget(OBJ_MGR, i))->type != OBJ_ENEMY; ++i)
			;

	if (obj->ext[BALL_EXT_COOLDOWN] > 0) {
		obj->ext[BALL_EXT_COOLDOWN]--;
		return 0;
	}
	else if (totalvel == 0) {
		if (rand() % 2 == 0)
			obj->hvel = BALL_START_VEL;
		else
			obj->hvel = -BALL_START_VEL;

		obj->vvel = rand() % (BALL_START_VEL * 2) - BALL_START_VEL;
	}

	tmp.x += obj->hvel;
	tmp.y += obj->vvel;

	if (chkhoob(tmp)) {
		if (tmp.x < 0)
			ENEMY_SCORE++;
		else
			PLAYER_SCORE++;

		printf("Current score: %d - %d\n", PLAYER_SCORE, ENEMY_SCORE);

		/* reset position and don't move for a couple seconds */
		obj->x = WIN_WIDTH / 2;
		obj->y = WIN_HEIGHT / 2;
		obj->hvel = 0;
		obj->vvel = 0;
		obj->ext[BALL_EXT_COOLDOWN] = BALL_COOLDOWN;
	}
	if (chkvoob(tmp))
		obj->vvel = -obj->vvel;

	/* check if intersects with either paddle */
	if (SDL_HasIntersection(&tmp, &player->spr.hb_rect))
		collobj = player;
	if (SDL_HasIntersection(&tmp, &enemy->spr.hb_rect))
		collobj = enemy;

	if (collobj) {
		/* change vertical velocity based on where it hit paddle */
		obj->vvel -= (collobj->y - obj->y) /
			BALL_ANGLE_MODIFIER;

		/* reverse direction */
		obj->hvel = -obj->hvel;

		/* increase horizontal velocity if it's not maxed out */
		if (totalvel < BALL_MAX_VELOCITY)
			obj->hvel *= BALL_VEL_INC_RATE;

		/* if inside of the paddle, get out of there! */
		if (collobj->type == OBJ_PLAYER) {
			while (SDL_HasIntersection(&obj->spr.hb_rect,
						&collobj->spr.hb_rect)) {
				obj->x++;
				obj->spr.hb_rect.x++;
			}
		} else {
			while (SDL_HasIntersection(&obj->spr.hb_rect,
						&collobj->spr.hb_rect)) {
				obj->x--;
				obj->spr.hb_rect.x--;
			}
		}
	}

	return 0;
}
