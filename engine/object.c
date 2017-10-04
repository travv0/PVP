#include "object.h"
#include "log.h"

int defaultstep(struct object *obj) { return 0; }

void updateall(void)
{
	unsigned int i;
	struct object *obj;

	/* clear renderer so objects can draw in their update functions */
	SDL_RenderClear(RENDERER);

	for (i = 0; i < objmcnt(OBJ_MGR); ++i) {
		obj = objmget(OBJ_MGR, i);

		obj->x += obj->hvel;
		obj->y += obj->vvel;

		obj->spr.dest_rect.x = obj->x;
		obj->spr.dest_rect.y = obj->y;

		obj->step(obj);
	}
}
