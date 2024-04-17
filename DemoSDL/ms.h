#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "entity.h"
class Ms {
public :
    Ms(SDL_Texture* MONS, int x, int y);
private:
    int posX;
    int posY;
};
