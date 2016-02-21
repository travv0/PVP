#include <stdio.h>

#include "game.h"
#include "error.h"
#include "basic.h"
#include "sprite.h"

int game_loop(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *screen)
{
	int done = FALSE;
	enum game_state state = PLAYING;

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

			SDL_Delay(3000);
			done = TRUE;

			break;
		case PAUSED:
			break;
		case MAIN_MENU:
			break;
		default:
			break;
			return throw_err(NO_STATE_ERR);
		}
	}

	SDL_FreeSurface(pl_sprite.surface);
	return 0;
}
