#include <math.h>

#include "sprite.h"
#include "log.h"

struct sprite SPRITE_DEFAULT = {
	NULL,
	0,
	0,
	1,
	NULL,
	NULL,
	1,
	0,
	FALSE,
	FALSE,
	FALSE
};

/* starts the animation from the current frame */
void anistart(struct sprite *spr, int loop)
{
	spr->animating = TRUE;
	spr->looping = loop;
}

/* sets animation speed */
void anispeed(struct sprite *spr, float speed)
{
	spr->speed = speed;
}

/* play animation in reverse */
void anireverse(struct sprite *spr, int reverse)
{
	spr->reverse = reverse;
}

/* stops the animation, preserving the current frame */
void anipause(struct sprite *spr)
{
	spr->animating = FALSE;
}

/* stops the animation, setting the current frame to the beginning */
void anistop(struct sprite *spr)
{
	spr->animating = FALSE;

	if (spr->reverse == FALSE)
		spr->curr_frame = 0;
	else
		spr->curr_frame = spr->frames - 1;
}

/* set the current frame */
void aniset(struct sprite *spr, int frame)
{
	spr->curr_frame = frame;
}

/* animates and blits the sprite */
void animate(struct sprite *spr, SDL_Surface *screen)
{
	if (spr->animating == TRUE)
	{
		/* stop animating if not set to looping and animation is done */
		if (spr->looping == FALSE &&
				(
				 /* if sprite isn't reversing, stop at last frame */
				 (!spr->reverse && spr->curr_frame == spr->frames - 1) ||
				 /* otherwise, stop at first */
				 (spr->reverse && spr->curr_frame <= 0)
				)
		   )
			anistop(spr);
		else if (spr->reverse)
			spr->curr_frame = (spr->curr_frame <= 0 ?
					spr->frames - spr->speed :
					spr->curr_frame - spr->speed);
		else
			spr->curr_frame = fmod(spr->curr_frame + spr->speed,
				(float)spr->frames);
	}
	spr->source_rect->x = spr->source_rect->w * (int)spr->curr_frame;
	SDL_BlitSurface(spr->surface, spr->source_rect, screen, spr->frame_rect);
}
