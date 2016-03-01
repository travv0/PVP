/* this file contains all errors and a function to throw them */
#ifndef __ERROR_H
#define __ERROR_H

#include <SDL2/SDL.h>

/* holds error message, unique error code,
 * and either ERROR to abort game or WARNING if it's not fatal */
struct error {
	char const *msg;
	int code;
	int type;
};

/* declare all errors here */
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
extern struct error OBJM_IDX_OOR;

/* give an error declared above to this function
 * and it'll take care of the rest */
void throw_err(struct error err);

#endif
