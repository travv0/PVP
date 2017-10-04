#include <SDL2/SDL.h>

#include "engine/basic.h"
#include "engine/object.h"
#include "data.h"
#include "recthlpr.h"

#define MOVE_SPEED	1.5

int playerstep(struct object *obj)
{
	static int mup, mdown;

	while (SDL_PollEvent(EVENT)) {
		switch (EVENT->type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			switch (EVENT->key.keysym.sym) {
			case SDLK_ESCAPE:
				exit(0);
				break;
			case SDLK_UP:
				mup = TRUE;
				break;
			case SDLK_DOWN:
				mdown = TRUE;
				break;
			}

			break;
		case SDL_KEYUP:
			switch (EVENT->key.keysym.sym) {
			case SDLK_UP:
				mup = FALSE;
				break;
			case SDLK_DOWN:
				mdown = FALSE;
				break;
			}

			break;
		}
	}

	if (mup == TRUE) {
		SDL_Rect tmp = obj->spr.hb_rect;
		tmp.y -= MOVE_SPEED;
		if (!chkvoob(tmp))
			obj->y -= MOVE_SPEED;
	}
	if (mdown == TRUE) {
		SDL_Rect tmp = obj->spr.hb_rect;
		tmp.y += MOVE_SPEED;
		if (!chkvoob(tmp))
			obj->y += MOVE_SPEED;
	}

	return 0;
}
