#include <SDL2/SDL.h>
#include "utils.h"

double getseconds(void) {
	return SDL_GetTicks() / 1000.0;
}

double sectomsec(double sec) {
	return sec * 1000;
}
