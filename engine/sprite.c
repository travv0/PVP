#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <math.h>

#include "log.h"
#include "error.h"
#include "strings.h"
#include "object.h"
#include "../basic.h"

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

	/* draw sprite from center */
	draw_rect.x = spr->dest_rect.x - spr->dest_rect.w / 2.0;
	draw_rect.y = spr->dest_rect.y - spr->dest_rect.h / 2.0;
	draw_rect.w = spr->dest_rect.w;
	draw_rect.h = spr->dest_rect.h;

	/* update hitbox position */
	spr->hb_rect.x = draw_rect.x + spr->hb_base_rect.x;
	spr->hb_rect.y = draw_rect.y + spr->hb_base_rect.y;

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

	if (spr->load) {
		surface = IMG_Load(fname);

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

	/* font stuff for scores */
	FONT = TTF_OpenFont("fonts/LiberationMono-Regular.ttf", 18);

	if (FONT == NULL) {
		throw_err(SDL_TTF_OPEN_ERR);
	}

	SDL_Color clrFg = {0, 0, 0, 255};

	char score[5];
	char enemyscore[5];
	snprintf(score, sizeof score, "%d", PLAYER_SCORE);
	snprintf(enemyscore, sizeof enemyscore, "%d", ENEMY_SCORE);
	SDL_Rect rcDest = {0, 0, 40, 50};
	SDL_Surface *sText = TTF_RenderText_Solid(FONT, score, clrFg);
	SDL_Texture *fonttx = SDL_CreateTextureFromSurface(RENDERER, sText);

	SDL_RenderCopy(RENDERER, fonttx,
		       NULL, &rcDest);

	rcDest.x = WIN_WIDTH - 40;

	SDL_Surface *enemysText = TTF_RenderText_Solid(FONT, enemyscore, clrFg);
	SDL_Texture *enemyfonttx = SDL_CreateTextureFromSurface(RENDERER, enemysText);

	SDL_RenderCopy(RENDERER, enemyfonttx,
		       NULL, &rcDest);

	SDL_FreeSurface(sText);
	SDL_FreeSurface(enemysText);

	TTF_CloseFont(FONT);

	SDL_RenderPresent(RENDERER);
}

/* FIXME: fix figure out how to not call initsprites() every time */
void sprchange(struct object *obj, struct sprite spr)
{
	obj->spr = spr;
	initsprites();
}
