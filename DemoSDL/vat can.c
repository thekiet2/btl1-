class Obstacle {
public:
    Obstacle(SDL_Renderer* renderer, const char* imagePath, int x, int y) {
        // Load hình ảnh từ file
        SDL_Surface* surface = IMG_Load(imagePath);
        if (!surface) {
            std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
            // Xử lý lỗi ở đây
        }

        // Tạo texture từ surface
        m_texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!m_texture) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
            // Xử lý lỗi ở đây
        }

        SDL_FreeSurface(surface);

        // Đặt vị trí của cản trở
        m_rect.x = x;
        m_rect.y = y;

        // Lấy kích thước của hình ảnh
        SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h);
    }

    ~Obstacle() {
        SDL_DestroyTexture(m_texture);
    }

    // Hiển thị cản trở lên màn hình
    void render(SDL_Renderer* renderer) {
        SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
    }

private:
    SDL_Texture* m_texture;
    SDL_Rect m_rect;
};
