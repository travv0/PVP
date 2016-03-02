#include "object.h"
#include "data.h"

int defaultstep(struct object *obj) {}

void updateall()
{
	int i;
	for (i = 0; i < objmcnt(OBJ_MGR); ++i)
		objmget(OBJ_MGR, i)->step(objmget(OBJ_MGR, i));
}

void initobjects()
{
	int i;
	for (i = 0; i < objmcnt(OBJ_MGR); ++i) {
		objmget(OBJ_MGR, i)->spr.dest_rect.x = objmget(OBJ_MGR, i)->x;
		objmget(OBJ_MGR, i)->spr.dest_rect.y = objmget(OBJ_MGR, i)->y;
	}
}
