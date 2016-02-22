#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "log.h"

#define ERROR 		1
#define WARNING		0
#define LOG_LINE_SIZE	1000

struct error TEST_ERROR = {
	"This is a test error",
	-1,
	ERROR
};
struct error TEST_WARNING = {
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

void throw_err(struct error err)
{
	char log[LOG_LINE_SIZE];
	snprintf(log, LOG_LINE_SIZE, "%s: %d %s: %s",
		(err.type == ERROR ? "ERROR" : "WARNING"),
		err.code,
		err.msg,
		SDL_GetError());
	logstr(log);
	if (err.type == ERROR)
		exit(err.code);
}
