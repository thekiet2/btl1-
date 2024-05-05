#include <SDL.h>
#include <SDL_image.h>
#include <cmath>
#include <vector>
#include <string>
#include "player.h"
#include "entity.h"
#include "ground.h"
using namespace std;
const float GRAVITY = 0.09f;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int ALIVE = 0;
const int CURSOR_DEATH = 1;
const int HOLE_DEATH = 2;
const int IMPACT_DEATH = 3;

Player::Player(float p_x, float p_y, vector<SDL_Texture*> p_tex)
	: Entity{ p_x, p_y, p_tex}
{
	setX(SCREEN_WIDTH/2 - getWidth()/2);
	setY(SCREEN_HEIGHT - getHeight() - 64);
}
float Player::distance()
{
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	return sqrt(pow((getX() + getWidth()/2) - mouseX, 2) + pow((getY() + getHeight()/2) - mouseY, 2));
}
bool Player::jump()
{
	if (distance() < 100)
	{
		if (grounded)
		{
			velocityY = -(1/distance() * 200);
			grounded = false;
			return true;
		}
	}
	return false;
}
float Player::clamp(float p_value, float p_min, float p_max){
	if (p_value > p_max)
		return p_max;
	if (p_value < p_min)
		return p_min;
	return p_value;
}
void Player::animEyes()
{
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	setAnisetX(0, clamp(mouseX - getX() - getWidth()/2, -2.5, 2.5));
	setAnisetY(0, clamp(mouseY - getY() - getHeight()/2 + 15, -2.5, 2.5));
}
bool Player::check(Player& entity1,  Star& entity2) {
    int left1 = entity1.getX();
    int right1 = left1 + entity1.getWidth();
    int top1 = entity1.getY();
    int bottom1 = top1 + entity1.getHeight();

    int left2 = entity2.getX();
    int right2 = left2 + entity2.getWidth();
    int top2 = entity2.getY();
    int bottom2 = top2 + entity2.getHeight();

    if (right1 >= left2 && left1 <= right2 && bottom1 >= top2 && top1 <= bottom2) {
        return true;
    }

    return false;
}
void Player::updatebonus(Player& entity1, Star& entity2){
    if(check(entity1, entity2) == 1){
        bonus += 100;
    }
}
void Player::update(Ground& ground)
{
	timer++;
	score = timer/50 + bonus;
	if (score > highscore)
	{
		highscore = score;
	}

	setX(getX() - 1);
	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	animEyes();
	setAnisetY(3, 0);
	setAnisetY(4, 0);

	if (distance() < 100)
	{
		setAnisetY(3, sin(SDL_GetTicks()/50) * velocityX - 2);
		setAnisetY(4, -sin(SDL_GetTicks()/50) * velocityX - 2 );
		if (mouseX < getX())
		{
			velocityX = 1/distance() * 100;
		}
		else if (mouseX > getX() + getWidth())
		{
			velocityX = 1/distance() * -100;
		}
		else
		{
			velocityX = 0;
			if (mouseY > getY() && mouseY < getY() + getHeight())
			{
				dead = CURSOR_DEATH;
			}
		}
	}
	else
	{
		velocityX = 0;
	}
	setX(getX() + velocityX);

	setY(getY() + velocityY);
	if (ground.isTileBelow(getX(), getWidth()))
	{
		if (getY() + getHeight() < SCREEN_HEIGHT - 64)
		{
			velocityY += GRAVITY;
			grounded = false;
		}
		else
		{
			if (getY() < SCREEN_HEIGHT - getHeight() - 64 + 20)
			{
				setY(SCREEN_HEIGHT - getHeight() - 64);
				grounded = true;
			}
		}
	}
	else
	{
			velocityY += GRAVITY;
			grounded = false;
			if (getY() > SCREEN_HEIGHT)
			{
				dead = HOLE_DEATH;
			}
	}

}
const char* Player::getScore()
{
	string s = to_string(score);
	s = "DISTANCE: " + s;
	return s.c_str();
}
const char* Player::getHighscore()
{
	string s = to_string(highscore);
	s = "HIGH SCORE: " + s;
	return s.c_str();
}
int Player::getScoreInt()
{
	return score;
}
int Player::isDead()
{
	return dead;
}
void Player::reset()
{
    setX(SCREEN_WIDTH/2 - getWidth()/2);
    setY(SCREEN_HEIGHT - getHeight() - 64);
    score = 0;
    timer = 0;
    velocityX = 0;
    velocityY = 0;
    dead = 0;
}
