#ifndef _GRAPHICS__H
#define _GRAPHICS__H
#include <string>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"

SDL_Surface* LoadImage(std::string file_path){
SDL_Surface *load_image = NULL;
SDL_Surface *optimize_image = NULL;
SDL_Window* window = nullptr; // Khai báo biến window và gán giá trị mặc định là nullptr
window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
SDL_Surface* screen_surface = nullptr; // Khai báo biến screen_surface và gán giá trị mặc định là nullptr
screen_surface = SDL_GetWindowSurface(window);
load_image = IMG_Load(file_path.c_str());
if (load_image != NULL) {
    optimize_image = SDL_ConvertSurface(load_image, screen_surface->format, 0);
    if (optimize_image == NULL) {
        std::cerr << "Unable to optimize image! SDL Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(load_image);
}
return optimize_image;
}
#endif // _GRAPHICS__H
