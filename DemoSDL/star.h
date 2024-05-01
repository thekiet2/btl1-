#pragma once;
#include <SDL.h>
#include <SDL_image.h>
#include<vector>
#include"ground.h"
using namespace std;
class Star
{
private:
    SDL_Texture* texture;
    int x;
    int y;
    int width;
    int height;

public:
    Star(SDL_Texture* star, int p_x, int p_y);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    SDL_Texture* getTexture() const {
        return texture;
    }

    void SetX(int p_x);
    void SetY(int p_y);
    void update(Ground& ground);
    int Vx;
    void reset();
};
