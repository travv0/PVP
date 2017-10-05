/* this file is to keep all the string literals in one place.
 * right now it's not used for log messages, but that might change */
#ifndef __IMAGEPATHS_H
#define __IMAGEPATHS_H

/* sprite files.
 * keep sprites in a directory with the name of their associated object */
#define SPR_DIR		"sprites/"

/* define individual sprite directories like this */
#define PLAYER_SPR_DIR	"player/"
#define PLAYER_SPR_PATH	SPR_DIR PLAYER_SPR_DIR "player.png"

#define DEFAULT_SPR	PLAYER_SPR_PATH

#endif
