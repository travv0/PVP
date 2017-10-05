/* this file is just to hold very basic stuff that will be used
 * in almost every other file */
#ifndef __BASIC_H
#define __BASIC_H

#include <SDL2/SDL.h>

#include "objmanager.h"
#include "sprite.h"

#define TRUE	1
#define FALSE	0

#define CUSTOM_TICK_MODIFIER	10.0

#define SPR_NONE {				/* SPR_NONE */		\
		"",			/* path to spritesheet */	\
		NULL,			/* texture (set to NULL) */	\
		1/TARGET_FRAME_RATE,	/* animation speed */		\
		{0, 0, 0, 0},		/* base rectangle (first frame of animation) */ \
		{0, 0, 0, 0},		/* source rectange */		\
		{0, 0, 0, 0},		/* destination rectangle of sprite */ \
		{0, 0, 0, 0},		/* base hitbox of sprite */	\
		{0, 0, 0, 0},		/* hitbox of sprite */		\
		0,			/* number of frames in animation */ \
		0,			/* starting frame */		\
		FALSE,			/* whether sprite should animate */ \
		FALSE,			/* whether sprite should loop */ \
		FALSE,			/* whether animation should play backwards */ \
		FALSE			/* whether the sprite should currently be loaded */ \
	}

extern int DEBUG;	/* whether or not to log things */
extern double DT;	/* change in time since last go in the main loop */

extern SDL_Window *WINDOW;	/* the main game window */
extern SDL_Renderer *RENDERER;	/* the main game renderer */
extern SDL_Texture *TEXTURE;	/* the main game texture */

extern SDL_Event *EVENT;	/* for catching events and handling them */

extern struct objm *OBJ_MGR;	/* global object manager */

#endif
