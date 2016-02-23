#ifndef __ERROR_H
#define __ERROR_H

#include "sdl.h"

struct error {
	char const *msg;
	int code;
	int type;
};

extern struct error TEST_ERR;
extern struct error TEST_WARN;
extern struct error SDL_INIT_ERR;
extern struct error SDL_WIND_ERR;
extern struct error SDL_REND_ERR;
extern struct error SDL_SURF_ERR;
extern struct error SDL_RECT_ERR;
extern struct error NO_STATE_ERR;
extern struct error SDL_BMP_ERR;
extern struct error LOG_OPEN_WARN;

void throw_err(struct error err);

#endif
