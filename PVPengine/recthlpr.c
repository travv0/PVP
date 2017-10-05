#include "recthlpr.h"
#include "../basic.h"	/* needed to get user-set windows size */

int chkoob(SDL_Rect r)
{
	if (chkhoob(r) || chkvoob(r))
		return 1;
	return 0;
}

int chkhoob(SDL_Rect r)
{
	if (r.x < 0 || r.x + r.w > WIN_WIDTH)
		return 1;
	return 0;
}

int chkvoob(SDL_Rect r)
{
	if (r.y < 0 || r.y + r.h > WIN_HEIGHT)
		return 1;
	return 0;
}
