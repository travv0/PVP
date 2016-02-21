#ifndef __GAME_H
#define __GAME_H

#include "sdl.h"

enum game_state { PLAYING, PAUSED, MAIN_MENU };

int game_loop(SDL_Window *, SDL_Renderer *, SDL_Surface *);

#endif
