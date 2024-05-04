#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include "renderwindow.h"
#include "entity.h"
#include "player.h"
#include "ground.h"
#include "mons.h"
#include "bkg.c"
#include "star.h"
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int ALIVE = 0;
const int CURSOR_DEATH = 1;
const int HOLE_DEATH = 2;

bool check(Player& entity1,  Star& entity2) {
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

bool check(Player& entity1,  Mons& entity2) {
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

RenderWindow window;

vector<SDL_Texture*> playerTex;
SDL_Texture* bk;
SDL_Texture* monster;
SDL_Texture* groundTex[4];
SDL_Texture* arrow;
SDL_Texture* highscoreBox;
SDL_Texture* deathOverlay;
SDL_Texture* logo;
SDL_Texture* mstex;
SDL_Texture* sao;
TTF_Font* font32;
TTF_Font* font32_outline;
TTF_Font* font24;
TTF_Font* font16;
SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
Mix_Chunk* jumpSfx;
Mix_Chunk* fallSfx;
Mix_Chunk* hitSfx;
Mix_Chunk* clickSfx;
bool gameRunning = true;
bool playedDeathSFX = false;
bool mainMenu = true;

bool init() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    window.create("Cursor Custodian", SCREEN_WIDTH, SCREEN_HEIGHT);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    srand((unsigned)time(0));

    playerTex.push_back(window.loadTexture("player_0.png"));
    playerTex.push_back(window.loadTexture("player_1.png"));
    playerTex.push_back(window.loadTexture("player_2.png"));
    playerTex.push_back(window.loadTexture("player_3.png"));
    playerTex.push_back(window.loadTexture("player_4.png"));

    groundTex[0] = window.loadTexture("left.png");
    groundTex[1] = window.loadTexture("center.png");
    groundTex[2] = window.loadTexture("right.png");
    groundTex[3] = window.loadTexture("hole.png");
    monster = window.loadTexture("object.png");
    bk = window.loadTexture("bkk.jpg");
    sao = window.loadTexture("ball.png");

    arrow = window.loadTexture("arrow.png");
    highscoreBox = window.loadTexture("highscore_box.png");
    deathOverlay = window.loadTexture("death_overlay.png");
    logo = window.loadTexture("logo.png");

    font32 = TTF_OpenFont("cocogoose.ttf", 32);
    font32_outline = TTF_OpenFont("cocogoose.ttf", 32);
    font24 = TTF_OpenFont("cocogoose.ttf", 24);
    font16 = TTF_OpenFont("cocogoose.ttf", 16);
    TTF_SetFontOutline(font32_outline, 3);

    jumpSfx = Mix_LoadWAV("jump.wav");
    fallSfx = Mix_LoadWAV("fall.wav");
    hitSfx = Mix_LoadWAV("hit.wav");
    clickSfx = Mix_LoadWAV("click.wav");
    Mix_PlayChannel(-1, jumpSfx, 0);

    return true;
}

bool load = init();

Player player(0, 0, playerTex);
Ground ground(groundTex[0], groundTex[1], groundTex[2], groundTex[3]);
Mons mon(monster, 10, 410);
Star saoplus(sao, 30, 450);
void reset() {
    player.reset();
    ground.reset();
    mon.reset();
    saoplus.reset();
}

void gameLoop() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                gameRunning = false;
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                if (mainMenu) {
                    if (event.button.button == SDL_BUTTON_LEFT && SDL_GetTicks() > 2500) {
                        mainMenu = false;
                        Mix_PlayChannel(-1, clickSfx, 0);
                    }
                } else {
                    if (event.button.button == SDL_BUTTON_LEFT && player.isDead() == ALIVE) {
                        if (player.jump()) {
                            Mix_PlayChannel(-1, jumpSfx, 0);
                        }
                    } else if (player.isDead() != ALIVE) {
                        Mix_PlayChannel(-1, clickSfx, 0);
                        reset();
                        playedDeathSFX = false;
                    }
                }
                break;
            }
        }
    }
    if (mainMenu) {
        if (SDL_GetTicks() < 2500) {
            window.clear();
            window.renderCenter(0, sin(SDL_GetTicks()/100) * 2 - 4, "Let's play game", font24, white);
            window.display();
        } else {
            window.clear();
            window.render(SCREEN_WIDTH/2 - 234, SCREEN_HEIGHT/2 - 94 - 30, logo);
            window.renderCenter(0, 90 + sin(SDL_GetTicks()/100) * 2, "Click to start", font24, white);
            for (int i = 0; i < ground.getLength(); i++) {
                window.render(ground.getTile(i));
            }
            window.display();
        }
    } else {
        if (player.isDead() != CURSOR_DEATH) {
            ground.update(player.getScoreInt());
        }

        if (player.isDead() == ALIVE) {
            player.update(ground);
            mon.update(ground);
        } else if (!playedDeathSFX) {
            if (player.isDead() == CURSOR_DEATH) {
                Mix_PlayChannel(-1, hitSfx, 0);
            } else if (player.isDead() == HOLE_DEATH) {
                Mix_PlayChannel(-1, fallSfx, 0);
            }
            playedDeathSFX = true;
        }
        window.clear();
        window.render(bk);
        window.render(player);
        window.render(mon);

        for (int i = 0; i < ground.getLength(); i++) {
            window.render(ground.getTile(i));
        }
        window.render(25, 30, arrow);
        window.render(62, 20, player.getScore(), font32_outline, black);
        window.render(65, 23, player.getScore(), font32, white);
        window.render(0, 65, highscoreBox);
        window.render(65, 64, player.getHighscore(), font16, white);
        if(check(player, mon) == 1){
            player.dead = 1;
        }

        if (player.isDead() != ALIVE ) {
            window.render(deathOverlay);
            if (player.isDead() == CURSOR_DEATH) {
                window.renderCenter(0, -24, "The cursor is deadly to the player...", font24, white);
            } else if (player.isDead() == HOLE_DEATH) {
                window.renderCenter(0, -24, "The hole had no bottom...", font24, white);
            }
            window.renderCenter(0, 12, "Click to retry.", font16, white);
        }

        window.display();
    }
}

int main(int argc, char* args[]) {

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(gameLoop, 0, 1);
    #else
    while (gameRunning) {
        gameLoop();
        SDL_Delay(16);
    }
    #endif

    window.cleanUp();
    TTF_CloseFont(font32);
    TTF_CloseFont(font32_outline);
    TTF_CloseFont(font24);
    TTF_CloseFont(font16);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
