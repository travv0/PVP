/* this file is code for creating and animating sprites */
#ifndef __SPRITE_H
#define __SPRITE_H

#include <SDL2/SDL.h>
#include "basic.h"

/* struct to hold details about the sprite.
 * it should not be used to store info that would be better suited
 * for the entity that the sprite is attached to (when I add entities) */
struct sprite {
	SDL_Surface	*surface;
	float		speed;
	SDL_Rect	*source_rect;
	SDL_Rect	*frame_rect;
	int		frames;
	float		curr_frame;
	int		animating;
	int		looping;
	int		reverse;
};

/* this holds the default info for a new sprite.
 * won't be necessary after the sprite struct is no longer public */
extern struct sprite SPRITE_DEFAULT;

/* start the sprite's animation from the current frame */
void anistart(struct sprite *spr, int loop);

/* set the animation speed */
void anispeed(struct sprite *spr, float speed);

/* whether to play the animation in reverse */
void anireverse(struct sprite *spr, int reverse);

/* pause the animation, keeping the current frame */
void anipause(struct sprite *spr);

/* stop the animation, setting the current frame
 * back to the beginning of the animation */
void anistop(struct sprite *spr);

/* set the current frame of the animation */
void aniset(struct sprite *spr, int frame);

/* this should be run every time the screen is redrawn
 * to animate and draw the sprite */
void animate(struct sprite *spr, SDL_Surface *screen);

#endif
