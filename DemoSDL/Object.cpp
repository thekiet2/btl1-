#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <vector>
#include <string>
#include "Object.h"
#include "entity.h"
#include "ground.h"
#include "player.cpp"
using namespace std;
 Object(float startX, float startY, SDL_Renderer* renderer) : x(startX), y(startY), velocityX(0), velocityY(0), speed(5), object(nullptr) {
        SDL_Surface* surface = IMG_Load("object.png");
        if (surface == nullptr) {
            std::cerr << "Failed to load image! SDL_image Error: " << IMG_GetError() << endl;
        } else {
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr) {
                std::cerr << "Failed to create texture from surface! SDL Error: " << SDL_GetError() << endl;
            }
            SDL_FreeSurface(surface);
        }
}
Object :: reset()
{
    velocityX = 5*(rand()%10);
    velocityY = 0;
}
