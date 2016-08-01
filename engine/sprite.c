#include <math.h>

#include "log.h"
#include "error.h"
#include "strings.h"
#include "object.h"

/* load a sprite */
void _sprload(struct sprite *spr, char *fname);

/* initialize sprite */
void _sprinit(struct sprite *spr);

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

	spr->source_rect.x = spr->base_rect.x + spr->source_rect.w * (int)spr->curr_frame;
	if (SDL_RenderCopy(RENDERER, spr->texture,
				&spr->source_rect, &spr->dest_rect) != 0) {
		throw_err(SDL_REND_COPY_ERR);
	}
}

void initsprites(void)
{
	int i;
	for (i = 0; i < objmcnt(OBJ_MGR); ++i) {
		_sprinit(&objmget(OBJ_MGR, i)->spr);
	}
}

void _sprinit(struct sprite *spr)
{
	_sprload(spr, spr->fname);
}

void _sprload(struct sprite *spr, char *fname)
{
	SDL_Surface *surface = NULL;
	if (spr->load) {
		surface = SDL_LoadBMP(fname);

		if (surface == NULL) {
			throw_err(SDL_BMP_ERR);
		}

		if ((spr->texture = SDL_CreateTextureFromSurface(RENDERER,
					surface)) == NULL)
			throw_err(SDL_TEXTURE_ERR);

		SDL_FreeSurface(surface);
	}
}

void unloadsprites(void)
{
	int i;
	for (i = 0; i < objmcnt(OBJ_MGR); ++i)
		SDL_DestroyTexture(objmget(OBJ_MGR, i)->spr.texture);
}

void drawall(void) {
	SDL_RenderClear(RENDERER);

	int i;
	for (i = 0; i < objmcnt(OBJ_MGR); ++i) {
		if (objmget(OBJ_MGR, i)->spr.texture != NULL)
			animate(&objmget(OBJ_MGR, i)->spr);
	}

	SDL_RenderPresent(RENDERER);
}

/* FIXME: fix figure out how to not call initsprites() every time */
void sprchange(struct object *obj, struct sprite spr)
{
	obj->spr = spr;
	initsprites();
}
