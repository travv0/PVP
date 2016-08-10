#include <SDL2/SDL.h>

#include "engine/basic.h"
#include "engine/object.h"
#include "data.h"

#define MOVE_SPEED	4

int playerstep(struct object *obj)
{
	static int mright, mleft, mup, mdown;

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
			case SDLK_RIGHT:
				mright = TRUE;
				break;
			case SDLK_LEFT:
				mleft = TRUE;
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
			case SDLK_RIGHT:
				mright = FALSE;
				break;
			case SDLK_LEFT:
				mleft = FALSE;
				break;
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

	// if (mright == TRUE) {
	// 	obj->x += MOVE_SPEED;
	// 	sprchange(obj, SPRITES[SPR_PLAYER_PADDLE]);
	// }
	// if (mleft == TRUE) {
	// 	obj->x -= MOVE_SPEED;
	// 	sprchange(obj, SPRITES[SPR_PLAYER_WALK_LEFT]);
	// }
	// if (mup == TRUE) {
	// 	obj->y -= MOVE_SPEED;
	// 	sprchange(obj, SPRITES[SPR_PLAYER_WALK_UP]);
	// }
	// if (mdown == TRUE) {
	// 	obj->y += MOVE_SPEED;
	// 	sprchange(obj, SPRITES[SPR_PLAYER_WALK_DOWN]);
	// }

	obj->spr.dest_rect.x = obj->x;
	obj->spr.dest_rect.y = obj->y;
}
