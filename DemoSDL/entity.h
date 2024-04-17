#pragma once;
#include <SDL.h>
#include <SDL_image.h>
#include<vector>
using namespace std;
class Entity
{
private:
	float x, y;
	vector<float> anisetsX;
	vector<float> anisetsY;
	SDL_Rect currentFrame;
	vector<SDL_Texture*> tex;
public:
	Entity(float p_x, float p_y, vector<SDL_Texture*> p_tex);
	Entity(float p_x, float p_y, SDL_Texture* p_tex);
	Enitity(SDL_Texture *p_tex);
	void init();
	float getX();
	float getY();
	int getWidth();
	int getHeight();
	int getSize();
	void setX(float p_x);
	void setY(float p_y);
	float getAnisetX(int p_index);
	float getAnisetY(int p_index);
	void setAnisetX(int p_index, int p_value);
	void setAnisetY(int p_index, int p_value);
	SDL_Texture* getTex(int p_index);
	SDL_Rect getCurrentFrame();
	void setTex(SDL_Texture* p_tex);
};
