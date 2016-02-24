#include "sdl.h"
#include "utils.h"

double getseconds() {
	return SDL_GetTicks() / 1000.0;
}

double sectomsec(double sec) {
	return sec * 1000;
}
