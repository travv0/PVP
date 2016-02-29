#include <math.h>

#include "sprite.h"
#include "log.h"
#include "error.h"
#include "strings.h"
#include "data.h"

struct sprite SPRITE_DEFAULT = {
	DEFAULT_SPR,
	NULL,
	1,
	NULL,
	NULL,
	1,
	0,
	FALSE,
	FALSE,
	FALSE,
	TRUE
};

void anistart(struct sprite *spr, int loop)
{
	spr->animating = TRUE;
	spr->looping = loop;
}

void anispeed(struct sprite *spr, float speed)
{
	spr->speed = speed;
}

void anireverse(struct sprite *spr, int reverse)
{
	spr->reverse = reverse;
}

void anipause(struct sprite *spr)
{
	spr->animating = FALSE;
}

void anistop(struct sprite *spr)
{
	spr->animating = FALSE;

	if (spr->reverse == FALSE)
		spr->curr_frame = 0;
	else
		spr->curr_frame = spr->frames - 1;
}

void aniset(struct sprite *spr, int frame)
{
	spr->curr_frame = frame;
}

void animate(struct sprite *spr)
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

	spr->source_rect.x = spr->source_rect.w * (int)spr->curr_frame;
	SDL_BlitSurface(spr->surface, &spr->source_rect, SCREEN, &spr->dest_rect);
}

void initsprites()
{
	int i;
	for (i = 0; i < NUMOFOBJECTS; ++i)
		sprinit(&OBJECTS[i]);

}

void sprinit(struct sprite *spr)
{
	if (spr->fname == NULL)		spr->fname = SPRITE_DEFAULT.fname;
	if (spr->surface == NULL)	spr->surface = SPRITE_DEFAULT.surface;
	if (spr->speed == -1)		spr->speed = SPRITE_DEFAULT.speed;
	if (spr->frames == -1)		spr->frames = SPRITE_DEFAULT.frames;
	if (spr->curr_frame == -1)	spr->curr_frame = SPRITE_DEFAULT.curr_frame;
	if (spr->animating == -1)	spr->animating = SPRITE_DEFAULT.animating;
	if (spr->looping == -1)		spr->looping = SPRITE_DEFAULT.looping;
	if (spr->reverse == -1)		spr->reverse = SPRITE_DEFAULT.reverse;
	if (spr->load == -1)		spr->load = SPRITE_DEFAULT.load;

	sprload(spr, spr->fname);
}

void sprload(struct sprite *spr, char *fname)
{
	if (spr->load) {
		spr->surface = SDL_LoadBMP(fname);

		if (spr->surface == NULL) {
			throw_err(SDL_BMP_ERR);
		}
	}
}
