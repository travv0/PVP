#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "log.h"

#define LOG_SIZE	1000

struct error TEST_ERROR = {
	"This is a test error",
	-1
};
struct error SDL_INIT_ERR = {
	"Could not initialize SDL",
	1
};
struct error SDL_WIND_ERR = {
	"Could not create error",
	2
};
struct error SDL_REND_ERR = {
	"Failed to create renderer",
	3
};
struct error SDL_SURF_ERR = {
	"Could not get surface",
	4
};
struct error SDL_RECT_ERR = {
	"Failed to create rectangle",
	5
};
struct error NO_STATE_ERR = {
	"No game state set",
	6
};
struct error SDL_BMP_ERR = {
	"Failed to load BMP",
	7
};

int throw_err(struct error err)
{
	char log[LOG_SIZE];
	snprintf(log, LOG_SIZE, "%d %s: %s\n", err.code, err.msg, SDL_GetError());
	logstr(log);
	return err.code;
}
