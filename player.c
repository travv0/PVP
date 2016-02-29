#include <SDL2/SDL.h>

#include "player.h"
#include "basic.h"
#include "object.h"

#define MOVE_SPEED	4

int plstep(struct object obj)
{
	int mright, mleft, mup, mdown;
	mright = mleft = mup = mdown = FALSE;

	SDL_Event *event = malloc(sizeof(*event));

	while (SDL_PollEvent(event)) {
		switch (event->type) {
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			switch (event->key.keysym.sym) {
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
			switch (event->key.keysym.sym) {
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

	if (mright == TRUE)
		obj.x += sectomsec(DT) / MOVE_SPEED;
	if (mleft == TRUE)
		obj.x -= sectomsec(DT) / MOVE_SPEED;
	if (mup == TRUE)
		obj.y -= sectomsec(DT) / MOVE_SPEED;
	if (mdown == TRUE)
		obj.y += sectomsec(DT) / MOVE_SPEED;

	obj.spr.dest_rect.x = obj.x;
	obj.spr.dest_rect.y = obj.y;

	free(event);
}
