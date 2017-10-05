#include "object.h"
#include "log.h"
#include "../basic.h"

int defaultstep(struct object *obj) { return 0; }

void updateall(void)
{
	unsigned int i;
	struct object *obj;
	SDL_Rect draw_rect;

	/* clear renderer so objects can draw in their update functions */
	SDL_RenderClear(RENDERER);

	for (i = 0; i < objmcnt(OBJ_MGR); ++i) {
		obj = objmget(OBJ_MGR, i);

		obj->x += obj->hvel * DT;
		obj->y += obj->vvel * DT;

		obj->spr.dest_rect.x = obj->x;
		obj->spr.dest_rect.y = obj->y;

		/* update hitbox position */
		draw_rect.x = obj->spr.dest_rect.x - obj->spr.dest_rect.w / 2.0;
		draw_rect.y = obj->spr.dest_rect.y - obj->spr.dest_rect.h / 2.0;
		draw_rect.w = obj->spr.dest_rect.w;
		draw_rect.h = obj->spr.dest_rect.h;

		obj->spr.hb_rect.x = draw_rect.x + obj->spr.hb_base_rect.x;
		obj->spr.hb_rect.y = draw_rect.y + obj->spr.hb_base_rect.y;

		obj->step(obj);
	}
}
