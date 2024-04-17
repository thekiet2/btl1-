#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "renderwindow.h"

class Obstacle {
private:
    SDL_Texture* texture;
    SDL_Rect position;
    float velocity;
    SDL_Renderer* renderer;

public:
    Obstacle(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int w, int h, float vel) : renderer(renderer), texture(texture), velocity(vel) {
        position = { x, y, w, h };
    }

    void update() {
        position.x -= static_cast<int>(velocity);
    }

    void render() {
        SDL_RenderCopy(renderer, texture, nullptr, &position);
    }

    SDL_Rect getPosition() const { return position; }
    float getVelocity() const { return velocity; }
};
