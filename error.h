#ifndef __ERROR_H
#define __ERROR_H

#include "sdl.h"

struct error {
	char const *msg;
	int code;
};

extern struct error TEST_ERROR;
extern struct error SDL_INIT_ERR;
extern struct error SDL_WIND_ERR;
extern struct error SDL_REND_ERR;
extern struct error SDL_SURF_ERR;
extern struct error SDL_RECT_ERR;
extern struct error NO_STATE_ERR;
extern struct error SDL_BMP_ERR;

int throw_err(struct error err);

#endif
