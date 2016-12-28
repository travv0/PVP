#include "object.h"

int defaultstep(struct object *obj) { return 0; }

void updateall(void)
{
	unsigned int i;
	struct object *obj;

	for (i = 0; i < objmcnt(OBJ_MGR); ++i) {
		obj = objmget(OBJ_MGR, i);
		obj->spr.dest_rect.x = obj->x;
		obj->spr.dest_rect.y = obj->y;
		obj->step(obj);
	}
}
