#include <SDL2/SDL.h>

#include "PVPengine/object.h"
#include "PVPengine/SDL_FontCache.h"
#include "PVPengine/log.h"
#include "basic.h"

int scoresstep(struct object *obj)
{
	FC_Font *font = FC_CreateFont();
	FC_LoadFont(font, RENDERER, "fonts/VeraMono.ttf", 20,
		    FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);

	FC_Draw(font, RENDERER, 40, 0, "%d", PLAYER_SCORE);
	FC_Draw(font, RENDERER, WIN_WIDTH - 50, 0, "%d", ENEMY_SCORE);

	FC_FreeFont(font);

	return 0;
}
