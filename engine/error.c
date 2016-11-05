#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "log.h"

#define ERROR		1
#define WARNING		0

#define TRACE(fmt, var) \
	(error_at_line(0, 0, __FILE__, __LINE__, "%s : " fmt, #var, var))

/* ERRORs abort the game and WARNINGs do not. */
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
struct error OBJM_IDX_OOR_WARN = {
	"Object manager: index out of range",
	9,
	WARNING
};
struct error MALLOC_FAILED_ERR = {
	"Malloc failed",
	10,
	ERROR
};
struct error OBJM_NOT_INIT_ERR = {
	"Object was added to uninitialized object manager",
	11,
	ERROR
};
struct error SDL_TEXTURE_ERR = {
	"Could not create texture",
	12,
	ERROR
};
struct error SDL_REND_COPY_ERR = {
	"Could not copy texture to renderer",
	13,
	ERROR
};
struct error SDL_IMG_INIT_ERR = {
	"Could not initialize image",
	14,
	ERROR
};
struct error SDL_CONV_SURF_ERR = {
	"Could not convert surface",
	15,
	ERROR
};
struct error SDL_TTF_INIT_ERR = {
	"Failed to initialize SDL_ttf",
	16,
	ERROR
};
struct error SDL_TTF_OPEN_ERR = {
	"Failed to open font",
	17,
	ERROR
};

/* calls the log function with the error provided,
 * then aborts the program if the message is an error */
void throw_err(struct error err)
{
	char log[LOG_LINE_SIZE];
	snprintf(log, LOG_LINE_SIZE, "%s: %s (%d): %s",
		(err.type == ERROR ? "ERROR" : "WARNING"),
		err.msg,
		err.code,
		SDL_GetError());
	log(log, "%s");
	if (err.type == ERROR)
		exit(err.code);
}
