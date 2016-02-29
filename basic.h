/* this file is just to hold very basic stuff that will be used
 * in almost every other file */
#include <SDL2/SDL.h>

#ifndef __BASIC_H
#define __BASIC_H

#define TRUE	1
#define FALSE	0

/* the frame rate we're trying to hit.
 * make sure this is a double so we don't have to worry about accidentally
 * demoting to int when using it. */
#define TARGET_FRAME_RATE	60.0

extern int DEBUG;	/* whether or not to log things */
extern double DT;	/* change in time since last go in the main loop */
extern double RENDER_TIMER;	/* time control for rendering */

extern SDL_Window *WINDOW;	/* the main game window */
extern SDL_Renderer *RENDERER;	/* the main game renderer */
extern SDL_Surface *SCREEN;	/* the main game surface */

extern SDL_Event *EVENT;	/* for catching events and handling them */

#endif
