#include"mons.h"
Mons::Mons(SDL_Texture* mon, int p_x, int p_y)
: texture(mon), x(p_x), y(p_y) {
    width = 0;
    height = 0;
    if (texture != nullptr) {
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }
}
int Mons::getX() const {
    return x;
}

int Mons::getY() const {
    return y;
}
int Mons::getWidth() const {
    return width;
}

int Mons::getHeight() const {
    return height;
}

void Mons::SetX(int p_x) {
    x = p_x;
}

void Mons::SetY(int p_y) {
    y = p_y;
}

void Mons::update(Ground& ground) {
    Vx = 1;
    if (getX() >= 0 && getX() <= 800) {
        SetX(getX() + Vx*2);
    } else {
        SetX(getX() - 800);
    }
}
void Mons::reset() {
    SetX(0);
}
