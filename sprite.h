#ifndef __SPRITE_H
#define __SPRITE_H

#include "sdl.h"
#include "basic.h"

struct sprite {
	SDL_Surface	*surface;
	float		x;
	float		y;
	float		speed;
	SDL_Rect	*source_rect;
	SDL_Rect	*frame_rect;
	int		frames;
	float		curr_frame;
	int		animating;
	int		looping;
	int		reverse;
};

extern struct sprite SPRITE_DEFAULT;

void anistart(struct sprite *spr, int loop);
void anispeed(struct sprite *spr, float speed);
void anireverse(struct sprite *spr, int reverse);
void anipause(struct sprite *spr);
void anistop(struct sprite *spr);
void aniset(struct sprite *spr, int frame);
void animate(struct sprite *spr, SDL_Surface *screen);

#endif
