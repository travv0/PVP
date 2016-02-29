#include "object.h"
#include "data.h"

void drawall() {
	int i;
	for (i = 0; i < NUMOFOBJECTS; ++i)
		animate(&OBJECTS[i].spr);

	SDL_UpdateWindowSurface(WINDOW);
}

void updateall() {
	int i;
	for (i = 0; i < NUMOFOBJECTS; ++i)
		OBJECTS[i].step(OBJECTS[i]);

	SDL_UpdateWindowSurface(WINDOW);
}
