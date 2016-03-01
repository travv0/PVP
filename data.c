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
		{				/* PLYR */
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
		0,
		0,
		plstep
	},
	{
		{				/* STUCK_PLYR */
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
		200,
		200,
		defaultstep
	}
};
