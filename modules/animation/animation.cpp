#include "animation.h"
#include "SDL2/SDL_render.h"

Animation::Animation() {}
Animation::Animation(std::vector<SDL_Texture*> frames, size_t frame_duration) : frames(frames), frame_duration(frame_duration), current_frame_duration(frame_duration) {}

void Animation::update(const float delta_time) {
    current_frame_duration -= delta_time * 1000;

    if (current_frame_duration <= 0) {
        this->next_frame();
    }
}

void Animation::draw(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, frames[current_frame], NULL, &this->transformer);
}

void Animation::next_frame() {
    current_frame_duration = frame_duration;
    current_frame++;

    if (current_frame >= frames.size()) {
        current_frame = 0;
    }
}

SDL_Texture* Animation::frame() const {
    return frames[current_frame];
}
