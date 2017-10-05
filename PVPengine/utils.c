#include <SDL2/SDL.h>
#include "utils.h"
#include "basic.h"

double getseconds(void) {
	return SDL_GetTicks() / 1000.0;
}

double getticks(void) {
	return SDL_GetTicks() / CUSTOM_TICK_MODIFIER;
}

double sectomsec(double sec) {
	return sec * 1000;
}
