#include "recthlpr.h"
#include "engine/basic.h"

int chkoob(SDL_Rect r)
{
	if (r.x - r.w / 2 < 0 || r.x + r.w / 2 > WIN_WIDTH ||
			r.y - r.h / 2 < 0 || r.y + r.h / 2 > WIN_HEIGHT)
		return 1;
	return 0;
}
