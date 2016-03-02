#include "object.h"
#include "data.h"

int defaultstep(struct object *obj) {}

void updateall()
{
	int i;
	struct object *obj;

	for (i = 0; i < objmcnt(OBJ_MGR); ++i) {
		obj = objmget(OBJ_MGR, i);
		obj->spr.dest_rect.x = obj->x;
		obj->spr.dest_rect.y = obj->y;
		obj->step(obj);
	}
}

void initobjects()
{
	int i;
	for (i = 0; i < objmcnt(OBJ_MGR); ++i) {
		objmget(OBJ_MGR, i)->spr.dest_rect.x = objmget(OBJ_MGR, i)->x;
		objmget(OBJ_MGR, i)->spr.dest_rect.y = objmget(OBJ_MGR, i)->y;
	}
}
