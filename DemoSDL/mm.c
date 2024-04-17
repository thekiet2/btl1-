#pragma once;
#include <SDL.h>
#include <SDL_image.h>
#include "entity.h"
using namespace std;
class Monster
{
public:
    // Constructor
    Monster(SDL_Texture* Mons, int x, int y) {
        posX = x;
        posY = y;
    }
private:
    int posX, posY; // Tọa độ x và y

};
