#include <math.h>
#include <SDL2/SDL_image.h>

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
	SDL_Rect draw_rect;
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

	spr->source_rect.x = spr->base_rect.x + spr->source_rect.w *
		(int)spr->curr_frame;

	/* update hitbox position */
	spr->hb_rect.x = spr->dest_rect.x + spr->hb_base_rect.x;
	spr->hb_rect.y = spr->dest_rect.y + spr->hb_base_rect.y;

	/* draw sprite from center */
	draw_rect.x = spr->dest_rect.x - spr->dest_rect.w / 2.0;
	draw_rect.y = spr->dest_rect.y - spr->dest_rect.h / 2.0;
	draw_rect.w = spr->dest_rect.w;
	draw_rect.h = spr->dest_rect.h;

	if (SDL_RenderCopy(RENDERER, spr->texture,
				&spr->source_rect, &draw_rect) != 0) {
		throw_err(SDL_REND_COPY_ERR);
	}
}

void initsprites(void)
{
	int i;
	for (i = 0; i < objmcnt(OBJ_MGR); ++i) {
		_sprload(&objmget(OBJ_MGR, i)->spr, objmget(OBJ_MGR, i)->spr.fname);
	}
}

void _sprload(struct sprite *spr, char *fname)
{
	SDL_Surface *surface = NULL;
	SDL_Surface *optsurface = NULL;

	if (spr->load) {
		surface = IMG_Load(fname);

		if (surface == NULL) {
			throw_err(SDL_BMP_ERR);
		}

		optsurface = SDL_ConvertSurface(surface, SCREEN->format, 0);

		if (optsurface == NULL) {
			throw_err(SDL_CONV_SURF_ERR);
		}

		if ((spr->texture = SDL_CreateTextureFromSurface(RENDERER,
					optsurface)) == NULL)
			throw_err(SDL_TEXTURE_ERR);

		SDL_FreeSurface(surface);
		SDL_FreeSurface(optsurface);
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
