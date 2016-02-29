#include "object.h"
#include "data.h"

void drawall() {
	int i;
	for (i = 0; i < NUMOFSPRITES; ++i)
		animate(&SPRITES[i]);

	SDL_UpdateWindowSurface(WINDOW);
}
