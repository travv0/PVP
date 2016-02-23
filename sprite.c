#include "sprite.h"
#include "log.h"

struct sprite SPRITE_DEFAULT = {
	NULL,
	0,
	0,
	NULL,
	NULL,
	1,
	0,
	FALSE,
	FALSE
};

/* starts the animation from the current frame */
void anistart(struct sprite *spr, int loop)
{
	spr->animating = TRUE;
	spr->looping = loop;
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
	spr->curr_frame = 0;
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
		if (spr->looping == FALSE && spr->curr_frame == spr->frames - 1)
			anistop(spr);
		else
			spr->curr_frame = (spr->curr_frame + 1) % spr->frames;
	}
	spr->source_rect->x = spr->source_rect->w * spr->curr_frame;
	SDL_BlitSurface(spr->surface, spr->source_rect, screen, spr->frame_rect);
}
