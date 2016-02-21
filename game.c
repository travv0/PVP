#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "error.h"
#include "basic.h"
#include "sprite.h"
#include "log.h"

#define MOVE_SPEED	4

int game_loop(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *screen)
{
	int done = FALSE;
	enum game_state state = PLAYING;
	int vertspd, horspd;

	SDL_Event *event = malloc(sizeof(SDL_Event));

	struct sprite pl_sprite = SPRITE_DEFAULT;
	pl_sprite.surface = SDL_LoadBMP("images/player/BLU.BMP");

	if (pl_sprite.surface == NULL) {
		fprintf(stderr, "Failed to load BMP: %s\n", SDL_GetError());
		return throw_err(SDL_BMP_ERR);
	}

	pl_sprite.frame_rect = &pl_sprite.surface->clip_rect;

	while (!done) {
		switch (state) {
		case PLAYING:
			SDL_BlitSurface(pl_sprite.surface, NULL, screen, pl_sprite.frame_rect);
			SDL_UpdateWindowSurface(window);

			horspd = vertspd = 0;

			if (SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255)) != 0) {
				return throw_err(SDL_RECT_ERR);
			}

			while (SDL_PollEvent(event)) {
				switch (event->type) {
				case SDL_QUIT:
					done = TRUE;
					break;
				case SDL_KEYDOWN:
					switch (event->key.keysym.sym) {
					case SDLK_ESCAPE:
						done = TRUE;
						break;
					case SDLK_RIGHT:
						horspd += MOVE_SPEED;
						break;
					case SDLK_LEFT:
						horspd -= MOVE_SPEED;
						break;
					case SDLK_UP:
						vertspd -= MOVE_SPEED;
						break;
					case SDLK_DOWN:
						vertspd += MOVE_SPEED;
						break;
					}

					break;
				}
				pl_sprite.frame_rect->x += horspd;
				pl_sprite.frame_rect->y += vertspd;
			}

			break;
		case PAUSED:
			break;
		case MAIN_MENU:
			break;
		default:
			return throw_err(NO_STATE_ERR);
		}
	}

	SDL_FreeSurface(pl_sprite.surface);
	return 0;
}
