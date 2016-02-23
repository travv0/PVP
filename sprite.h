#ifndef __SPRITE_H
#define __SPRITE_H

#include "sdl.h"
#include "basic.h"

struct sprite {
	SDL_Surface	*surface;
	float		x;
	float		y;
	SDL_Rect	*source_rect;
	SDL_Rect	*frame_rect;
	int		frames;
	int		curr_frame;
	int		animating;
	int		looping;
};

extern struct sprite SPRITE_DEFAULT;

void anistart(struct sprite *spr, int loop);
void anipause(struct sprite *spr);
void anistop(struct sprite *spr);
void aniset(struct sprite *spr, int frame);
void animate(struct sprite *spr, SDL_Surface *screen);

#endif
