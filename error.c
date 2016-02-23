#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "log.h"

#define ERROR 		1
#define WARNING		0

/* Errors should end in _ERR and warnings should end in _WARN.
 * SDL related errors should start with SDL_.
 * ERRORs abort the game and WARNINGs do not. */
struct error TEST_ERR = {
	"This is a test error",
	-1,
	ERROR
};
struct error TEST_WARN = {
	"This is a test warning",
	-2,
	WARNING
};
struct error SDL_INIT_ERR = {
	"Could not initialize SDL",
	1,
	ERROR
};
struct error SDL_WIND_ERR = {
	"Could not create window",
	2,
	ERROR
};
struct error SDL_REND_ERR = {
	"Failed to create renderer",
	3,
	ERROR
};
struct error SDL_SURF_ERR = {
	"Could not get surface",
	4,
	ERROR
};
struct error SDL_RECT_ERR = {
	"Failed to create rectangle",
	5,
	ERROR
};
struct error NO_STATE_ERR = {
	"No game state set",
	6,
	ERROR
};
struct error SDL_BMP_ERR = {
	"Failed to load BMP",
	7,
	ERROR
};
struct error LOG_OPEN_WARN = {
	"Couldn't open log file",
	8,
	WARNING
};

void throw_err(struct error err)
{
	char log[LOG_LINE_SIZE];
	snprintf(log, LOG_LINE_SIZE, "%s: %s (%d): %s",
		(err.type == ERROR ? "ERROR" : "WARNING"),
		err.msg,
		err.code,
		SDL_GetError());
	logstr(log);
	if (err.type == ERROR)
		exit(err.code);
}
