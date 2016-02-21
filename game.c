#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "error.h"
#include "basic.h"
#include "sprite.h"

int game_loop(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *screen)
{
	int done = FALSE;
	enum game_state state = PLAYING;

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
			SDL_BlitSurface(pl_sprite.surface, NULL, screen, NULL);
			SDL_UpdateWindowSurface(window);

			while (SDL_PollEvent(event)) {
				switch (event->type) {
				case SDL_QUIT:
					done = TRUE;
					break;
				case SDL_KEYDOWN:
					switch (event->key.keysym.sym) {
					case SDLK_RIGHT:
						pl_sprite.frame_rect->x++;
						break;
					}
					break;
				}
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
