#include"star.h"
 Star::Star(SDL_Texture* star, int p_x, int p_y)
: texture(star), x(p_x), y(p_y) {
    width = 0;
    height = 0;
    if (texture != nullptr) {
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }
}
int Star::getX() const {
    return x;
}

int Star::getY() const {
    return y;
}
int Star::getWidth() const {
    return width;
}

int Star::getHeight() const {
    return height;
}

void Star::SetX(int p_x) {
    x = p_x;
}

void Star::SetY(int p_y) {
    y = p_y;
}

void Star::update(Ground& ground) {
    Vx = 1;
    if (getX() >= 0 && getX() <= 800) {
        SetX(getX() + Vx*2);
    } else {
        SetX(getX() - 800);
    }
}
void Star::reset() {
    SetX(0);
}
void Star::resetagain(){
    SetX(getX() + 800 + rand()%800);
}

