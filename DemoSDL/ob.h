#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "entity.h"
using namespace std;
const int MONSTER_WIDTH = 40;
const int MONSTER_HEIGHT = 40;
class Monster {
public:
    int x, y;
    SDL_Texture* texture;

    Monster(SDL_Texture* tex) : texture(tex) {
        x = rand() % (480- MONSTER_WIDTH);
        y = rand() % (800 - MONSTER_HEIGHT);
    }

    void move() {
        x += (rand() % 3 - 1);
        y += (rand() % 3 - 1);
    }

    void render(SDL_Renderer* renderer) {
        SDL_Rect rect = {x, y, MONSTER_WIDTH, MONSTER_HEIGHT};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
};
