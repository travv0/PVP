#include "data.h"
#include "str.h"
#include "basic.h"
#include "PVPengine/sprite.h"

int defaultstep(struct object *);
int playerstep(struct object *);

struct sprite SPRITES[NUMOFSPRITES] = {
	{				/* SPR_PLAYER */
		PLAYER_SPR_PATH,	/* path to spritesheet */
		NULL,			/* texture (set to NULL) */
		1/TARGET_FRAME_RATE,	/* animation speed */
		{0, 0, 50, 100},	/* base rectangle (first frame of animation) */
		{0, 0, 50, 100},	/* source rectange */
		{0, 0, 50, 100},	/* destination rectangle of sprite */
		{10, 5, 30, 90},		/* base hitbox of sprite */
		{10, 5, 30, 90},		/* hitbox of sprite */
		0,			/* number of frames in animation */
		0,			/* starting frame */
		FALSE,			/* whether sprite should animate */
		FALSE,			/* whether sprite should loop */
		FALSE,			/* whether animation should play backwards */
		TRUE			/* whether the sprite should currently be loaded */
	},
};

/* array of all objects in the game
 * use NULL for pointers, -1 for numbers, or
 * defaultstep for step function for default values
 * step functions should be named <object name>step */
struct object OBJECTS[NUMOFOBJECTS] = {
	{
		OBJ_DEFAULT,			/* object type */
		SPR_NONE,			/* default sprite to use */
		0,				/* x coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* y coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* horizontal velocity */
		0,				/* vertical velocity */
		defaultstep,			/* pointer to step function */
		{}
	},
	{
		OBJ_PLAYER,			/* object type */
		SPR_NONE,			/* default sprite to use */
		0,				/* x coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* y coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* horizontal velocity */
		0,				/* vertical velocity */
		playerstep,			/* pointer to step function */
		{}
	},
};
