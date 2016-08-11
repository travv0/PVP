#include <SDL2/SDL.h>

/* check if rectangle is outside of window */
int chkoob(SDL_Rect r);

/* check if rectangle is outside of window, horizontally */
int chkhoob(SDL_Rect r);

/* check if rectangle is outside of window, vertically */
int chkvoob(SDL_Rect r);

/* check if two rectangles intersect */
int chkintrsct(SDL_Rect r1, SDL_Rect r2);
