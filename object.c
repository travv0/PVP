#include "object.h"
#include "data.h"

void updateall() {
	int i;
	for (i = 0; i < NUMOFOBJECTS; ++i)
		OBJECTS[i].step(&OBJECTS[i]);
}
