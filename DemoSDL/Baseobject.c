#ifndef _BASEOBJECT_H_
#define _BASEOBJECT_H_
#include "basic function.c"
class Baseobject{// tuong tu graphics trong code co Chau
public:
    void SetRect(const int& x, const int& y){
    rect_.x = x;
    rect_.y = y;
    }
    SDL_Rect GetRect() const{
    return rect_;
    }
    SDL_Texture* GetObject() const{
    return p_object_;
    }
    bool LoadImage(std::string path, SDL_Renderer* screen)//ham load anh
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL); // render len cua so
protected:
    SDL_Texture* p_object_ ; // ham nap hinh anh vao texture p_object

    SDL_Rect rect; // ham luu kich thuoc
};
Baseobject :: Baseobject(){
p_object_ = NULL;
rect_x = 0;
rect_y = 0;
rect_w = 0;
rect_h = 0;
}
Baseobject :: Baseobject(){
// ...
}
bool Baseobject :: Loading(std ::  string path, SDL_Renderer* screen){
SDL_Texture* new_text = NULL;
SDL_Surface* load_surface = IMG_Load(path.c_str());//load hinh anh
if(load_surface != NULL){//ktra surface
    SDL_SetColorKey(load_surface, SDL_True, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));// xoa phong nen ben ngoai hinh anh nhan vat
    new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
    if(new_text != NULL){
        rect_w = load_surface->w;
        rect_h = load_surface->h;
    }
    SDL_FreeSurface(load_surface);// co the free vi da chuyen vao new_texture
}
p_object = new_texture;
return p_object_ != NULL;
}



#endif // _BASEOBJECT_H_
