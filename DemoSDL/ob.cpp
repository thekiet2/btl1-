#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <vector>
#include <string>
#include "ob.h"
using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
Objector :: Objector(float x, float y, SDL_Texture *p)
{

}
void Objector ::update()
{
    x = x + speed;
}
void Objector ::reset()
{
     x = (SCREEN_WIDTH/5);
     y = (SCREEN_HEIGHT - 64);
}
