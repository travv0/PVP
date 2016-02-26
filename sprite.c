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

void anistart(struct sprite *spr, int loop)
{
	spr->animating = TRUE;
	spr->looping = loop;
}

void anipause(struct sprite *spr)
{
	spr->animating = FALSE;
}

void anistop(struct sprite *spr)
{
	spr->animating = FALSE;
	spr->curr_frame = 0;
}

void aniset(struct sprite *spr, int frame)
{
	spr->curr_frame = frame;
}

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
