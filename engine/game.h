/* this is the testing file.
 * if something in this file is crucial to the engine,
 * it needs to be moved elsewhere at some point. */
#ifndef __GAME_H
#define __GAME_H

#include <SDL2/SDL.h>

/* enum for the game state */
enum game_state { PLAYING, PAUSED, MAIN_MENU };

/* the main game loop.
 * eventually, no engine code should be in here, only testing code */
void game_loop(void);

#endif
