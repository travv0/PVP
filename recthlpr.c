#include "recthlpr.h"
#include "engine/basic.h"

int chkoob(SDL_Rect r)
{
	if (r.x - r.w / 2.0 < 0 || r.x + r.w / 2.0 > WIN_WIDTH ||
			r.y - r.h / 2.0 < 0 || r.y + r.h / 2.0 > WIN_HEIGHT)
		return 1;
	return 0;
}

int chkhoob(SDL_Rect r)
{
	if (r.x - r.w / 2.0 < 0 || r.x + r.w / 2.0 > WIN_WIDTH)
		return 1;
	return 0;
}

int chkvoob(SDL_Rect r)
{
	if (r.y - r.h / 2.0 < 0 || r.y + r.h / 2.0 > WIN_HEIGHT)
		return 1;
	return 0;
}
