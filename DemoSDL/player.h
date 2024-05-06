#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "star.h"
#include "entity.h"
#include "ground.h"

using namespace std;

class Player : public Entity {
public:
	Player(float p_x, float p_y, vector<SDL_Texture*> p_tex);
	bool check(Player& entity1,  Star& entity2);
	void updatebonus(Player& entity1, Star& entity2);
	float distance();
	bool jump();
	void update(Ground& ground, Star& star);
	const char* getScore();
	const char* getHighscore();
	int getScoreInt();
	int isDead();
	void reset();
	int dead = 0;
	void updatebonus();
private:
	float velocityX, velocityY;
	bool grounded;
	void animEyes();
	float clamp(float p_value, float p_min, float p_max);
	int score = 0;
	int highscore = 0;
	int timer = 0;
	int bonus = 0;
};
