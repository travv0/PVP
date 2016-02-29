#include "object.h"
#include "data.h"

int defaultstep(struct object *obj) {}

void updateall()
{
	int i;
	for (i = 0; i < NUMOFOBJECTS; ++i)
		OBJECTS[i].step(&OBJECTS[i]);
}

void initobjects()
{
	int i;
	for (i = 0; i < NUMOFOBJECTS; ++i) {
		OBJECTS[i].spr.dest_rect.x = OBJECTS[i].x;
		OBJECTS[i].spr.dest_rect.y = OBJECTS[i].y;
	}
}
