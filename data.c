#include "data.h"
#include "strings.h"
#include "basic.h"

int plstep();
int defaultstep();

/* array of all sprites in the game
 * use NULL for pointers, -1 for numbers, or
 * defaultstep for step function for default values */
struct object OBJECTS[NUMOFOBJECTS] = {
	{
		{				/* OBJ_PLAYER */
			PLAYER_SPR,		/* path to spritesheet */
			NULL,			/* surface (set to NULL) */
			1/TARGET_FRAME_RATE,	/* animation speed */
			{0, 0, 200, 144},	/* source rectange of first sprite in animation */
			{0, 0, 200, 144},	/* destination rectangle of sprite */
			3,			/* number of frames in animation */
			0,			/* starting frame */
			TRUE,			/* whether sprite should animate */
			TRUE,			/* whether sprite should loop */
			FALSE,			/* whether animation should play backwards */
			TRUE			/* whether the sprite should currently be loaded */
		},
		0,				/* x coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* y coordinate.
						   leave at 0 because it's set by objmadd*/
		plstep				/* pointer to step function */
	},
	{
		{				/* OBJ_DEFAULT */
			PLAYER_SPR,		/* path to spritesheet */
			NULL,			/* surface (set to NULL) */
			1/TARGET_FRAME_RATE,	/* animation speed */
			{0, 0, 200, 144},	/* size of individual sprites on sheet */
			{0, 0, 200, 144},	/* destination rectangle of sprite */
			3,			/* number of frames in animation */
			0,			/* starting frame */
			TRUE,			/* whether sprite should animate */
			TRUE,			/* whether sprite should loop */
			FALSE,			/* whether animation should play backwards */
			TRUE			/* whether the sprite should currently be loaded */
		},
		0,				/* x coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* y coordinate.
						   leave at 0 because it's set by objmadd*/
		defaultstep			/* pointer to step function */
	}
};
