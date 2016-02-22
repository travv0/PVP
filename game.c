#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "error.h"
#include "basic.h"
#include "sprite.h"
#include "log.h"
#include "strings.h"

#define MOVE_SPEED	1

int game_loop(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *screen)
{
	int done = FALSE;
	enum game_state state = PLAYING;
	int mright, mleft, mup, mdown;

	mright = mleft = mup = mdown = 0;

	SDL_Event *event = malloc(sizeof(*event));

	struct sprite pl_sprite = SPRITE_DEFAULT;
	pl_sprite.surface = SDL_LoadBMP(PLAYER_SPR);

	if (pl_sprite.surface == NULL) {
		throw_err(SDL_BMP_ERR);
	}

	pl_sprite.frame_rect = &pl_sprite.surface->clip_rect;

	while (!done) {
		switch (state) {
		case PLAYING:
			SDL_BlitSurface(pl_sprite.surface, NULL, screen, pl_sprite.frame_rect);
			SDL_UpdateWindowSurface(window);

			if (SDL_FillRect(screen, NULL,
						SDL_MapRGB(screen->format, 255, 255, 255)) != 0) {
				throw_err(SDL_RECT_ERR);
			}

			while (SDL_PollEvent(event)) {
				switch (event->type) {
				case SDL_QUIT:
					done = TRUE;
					break;
				case SDL_KEYDOWN:
					switch (event->key.keysym.sym) {
					case SDLK_ESCAPE:
						logstr("Escape key pressed");
						done = TRUE;
						break;
					case SDLK_RIGHT:
						logstr("Right key pressed");
						mright = TRUE;
						break;
					case SDLK_LEFT:
						logstr("Left key pressed");
						mleft = TRUE;
						break;
					case SDLK_UP:
						logstr("Up key pressed");
						mup = TRUE;
						break;
					case SDLK_DOWN:
						logstr("Down key pressed");
						mdown = TRUE;
						break;
					}

					break;
				case SDL_KEYUP:
					switch (event->key.keysym.sym) {
					case SDLK_RIGHT:
						logstr("Right key released");
						mright = FALSE;
						break;
					case SDLK_LEFT:
						logstr("Left key released");
						mleft = FALSE;
						break;
					case SDLK_UP:
						logstr("Up key released");
						mup = FALSE;
						break;
					case SDLK_DOWN:
						logstr("Down key released");
						mdown = FALSE;
						break;
					}

					break;
				}
			}

			if (mright == TRUE)
				pl_sprite.frame_rect->x += MOVE_SPEED;
			if (mleft == TRUE)
				pl_sprite.frame_rect->x -= MOVE_SPEED;
			if (mup == TRUE)
				pl_sprite.frame_rect->y -= MOVE_SPEED;
			if (mdown == TRUE)
				pl_sprite.frame_rect->y += MOVE_SPEED;

			break;
		case PAUSED:
			break;
		case MAIN_MENU:
			break;
		default:
			throw_err(NO_STATE_ERR);
		}
	}

	free(event);
	SDL_FreeSurface(pl_sprite.surface);
	return 0;
}
