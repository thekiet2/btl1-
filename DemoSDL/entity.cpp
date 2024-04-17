#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "entity.h"
using namespace std;
Entity::Entity(float p_x, float p_y, std::vector<SDL_Texture*> p_tex)
:x(p_x), y(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	SDL_QueryTexture(p_tex.at(0), NULL, NULL, &currentFrame.w, &currentFrame.h);
	for (int i = 0; i < getSize(); i++)
	{
		anisetsX.push_back(0);
		anisetsY.push_back(0);
	}
}

Entity::Entity(float p_x, float p_y, SDL_Texture* p_tex)
:x(p_x), y(p_y)
{
	tex.push_back(p_tex);
	currentFrame.x = 0;
	currentFrame.y = 0;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
	for (int i = 0; i < getSize(); i++)
	{
		anisetsX.push_back(0);
		anisetsY.push_back(0);
	}
}
float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

int Entity::getWidth()
{
	return currentFrame.w;
}

int Entity::getHeight()
{
	return currentFrame.h;
}

int Entity::getSize()
{
	return tex.size();
}

void Entity::setX(float p_x)
{
	x = p_x;
}

void Entity::setY(float p_y)
{
	y = p_y;
}

float Entity::getAnisetX(int p_index)
{
	return anisetsX.at(p_index);
}

float Entity::getAnisetY(int p_index)
{
	return anisetsY.at(p_index);
}

void Entity::setAnisetX(int p_index, int p_value)
{
	anisetsX[p_index] = p_value;
}

void Entity::setAnisetY(int p_index, int p_value)
{
	anisetsY[p_index] = p_value;
}

SDL_Texture* Entity::getTex(int p_index)
{
	return tex.at(p_index);
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

void Entity::setTex(SDL_Texture* p_tex)
{
	tex[0] = p_tex;
}
