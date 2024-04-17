#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
class Monster{
private:
    SDL_Texture *monster;
    float m, n;
    float speed = 5;
public:
    void update();
    void reset();
};
