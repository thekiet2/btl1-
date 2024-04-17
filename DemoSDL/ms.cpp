#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <vector>
#include <string>
#include "entity.h"
#include "renderwindow.h"
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
Ms::Ms(SDL_Texture* MONS,int x, int y){
    MONSTEX = window.loadTexture("object.png");
    posX = x;
    posY = y;

}
