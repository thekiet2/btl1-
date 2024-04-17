#pragma once
#include<iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "entity.h"
#include "mons.h"
using namespace std;
class RenderWindow
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
public:
    RenderWindow();
    void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer);
    void create(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_filepath);
    void clear();
    void render(Entity& p_entity);
    void render(float p_x, float p_y, SDL_Texture* p_text);
    void render(SDL_Texture* p_text);
    void render(float p_x, float p_y, Mons& p_mons, TTF_Font* font, SDL_Color textColor);
void render(Mons &mons);
    void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
    void renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
    void display();
    void cleanUp();
};

