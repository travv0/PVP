#ifndef __SPRITE_H
#define __SPRITE_H

#include "sdl.h"

struct sprite {
	SDL_Surface	*surface;
	SDL_Rect	*frame_rect;
	int		frames;
	int		curr_frame;
};

struct sprite SPRITE_DEFAULT = {
	NULL,
	NULL,
	1,
	1
};

#endif
