#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "error.h"
#include "basic.h"
#include "sprite.h"
#include "log.h"
#include "strings.h"

#define MOVE_SPEED	400

int game_loop(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *screen)
{
	int done = FALSE;
	enum game_state state = PLAYING;
	int mright, mleft, mup, mdown;

	float dt; //delta time in seconds
	float clock; //last time sample in seconds
	float render_timer; //time control for rendering

	dt = 0.0;
	render_timer = 0.0; //init the render timer
	clock = SDL_GetTicks() / 1000.0f; //API callback to get the current time in seconds

	mright = mleft = mup = mdown = 0;

	SDL_Event *event = malloc(sizeof(*event));

	struct sprite pl_sprite = SPRITE_DEFAULT;
	pl_sprite.surface = SDL_LoadBMP(PLAYER_SPR);

	if (pl_sprite.surface == NULL) {
		throw_err(SDL_BMP_ERR);
	}

	pl_sprite.frames = 3;
	pl_sprite.frame_rect = malloc(sizeof(*(pl_sprite.frame_rect)));
	pl_sprite.frame_rect->x = 0;
	pl_sprite.frame_rect->y = 0;
	pl_sprite.frame_rect->w = 200;
	pl_sprite.frame_rect->h = 144;

	pl_sprite.source_rect = malloc(sizeof(*(pl_sprite.source_rect)));
	*(pl_sprite.source_rect) = *(pl_sprite.frame_rect);

	logstr("Entering main game loop");
	while (!done) {
		dt = SDL_GetTicks() / 1000.0f - clock; //get the current delta time for this frame
		clock = SDL_GetTicks() / 1000.0f; //updates the clock to check the next delta time

		switch (state) {
		case PLAYING:
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
				pl_sprite.frame_rect->x += MOVE_SPEED * dt;
			if (mleft == TRUE)
				pl_sprite.frame_rect->x -= MOVE_SPEED * dt;
			if (mup == TRUE)
				pl_sprite.frame_rect->y -= MOVE_SPEED * dt;
			if (mdown == TRUE)
				pl_sprite.frame_rect->y += MOVE_SPEED * dt;

			logint(dt);

			if (render_timer >= (1.0f/60.0f)) //checks if the frame is ready to render
			{
				animate(&pl_sprite, screen);
				SDL_UpdateWindowSurface(window);

				if (SDL_FillRect(screen, NULL,
							SDL_MapRGB(screen->format, 255, 255, 255)) != 0) {
					throw_err(SDL_RECT_ERR);
				}

				render_timer -= (1.0f/60.0f); //do not set to zero, remove the accumulated frame time to avoid skipping
			}

			render_timer += dt; //updates the render timer

			break;
		case PAUSED:
			break;
		case MAIN_MENU:
			break;
		default:
			throw_err(NO_STATE_ERR);
		}

	}
	logstr("Left main game loop");

	free(event);
	SDL_FreeSurface(pl_sprite.surface);
	return 0;
}
