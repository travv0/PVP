#include "data.h"
#include "str.h"
#include "PVPengine/basic.h"
#include "basic.h"
#include "PVPengine/sprite.h"

int playerstep(struct object *);
int enemystep(struct object *);
int ballstep(struct object *);
int scoresstep(struct object *);
int defaultstep(struct object *);

struct sprite SPRITES[NUMOFSPRITES] = {
	{				/* SPR_PADDLE */
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
	{				/* SPR_BALL */
		BALL_SPR_PATH,	/* path to spritesheet */
		NULL,			/* texture (set to NULL) */
		1/TARGET_FRAME_RATE,	/* animation speed */
		{0, 0, 50, 40},	/* base rectangle (first frame of animation) */
		{0, 0, 50, 40},	/* source rectange */
		{0, 0, 50, 40},	/* destination rectangle of sprite */
		{10, 5, 30, 30},		/* base hitbox of sprite */
		{10, 5, 30, 30},		/* hitbox of sprite */
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
	{
		OBJ_ENEMY,			/* object type */
		SPR_NONE,			/* default sprite to use */
		0,				/* x coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* y coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* horizontal velocity */
		0,				/* vertical velocity */
		enemystep,			/* pointer to step function */
		{}
	},
	{
		OBJ_BALL,			/* object type */
		SPR_NONE,			/* default sprite to use */
		0,				/* x coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* y coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* horizontal velocity */
		0,				/* vertical velocity */
		ballstep,			/* pointer to step function */
		{BALL_COOLDOWN}
	},
	{
		OBJ_SCORES,			/* object type */
		SPR_NONE,			/* default sprite to use */
		0,				/* x coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* y coordinate.
						   leave at 0 because it's set by objmadd*/
		0,				/* horizontal velocity */
		0,				/* vertical velocity */
		scoresstep,			/* pointer to step function */
		{}
	},
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
};
