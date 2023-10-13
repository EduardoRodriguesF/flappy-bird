#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include <vector>

class Animation {
public:
    Animation();
    Animation(std::vector<SDL_Texture*> frames, size_t frame_duration);
    void update(const float delta_time);
    void draw(SDL_Renderer* renderer);
    void next_frame();
    SDL_Texture* frame() const;

    std::vector<SDL_Texture*> frames;
    SDL_Rect transformer;
private:
    size_t current_frame = 0;
    size_t frame_duration = 0;
    int current_frame_duration = 0;
};
