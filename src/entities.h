#pragma once

#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"
#include "resource/texture.h"
#include "animation/animation.h"
#include <vector>

struct Player {
    Player(float x, float y);
    SDL_FPoint position;
    SDL_FPoint velocity;
    SDL_FRect collider;
    double angle;
    void update(const float &delta_time);
    void draw_collider(SDL_Renderer *renderer);
    void jump();
    Animation animation;
};

struct Pipe {
    Pipe(int gap_y);
    SDL_FRect bottom_body;
    SDL_FRect top_body;
    bool passed = false;
};

struct MovingScenerio {
    MovingScenerio(const Texture *texture, float speed, int y);
    const Texture *texture;
    float speed;
    int y;
    std::vector<float> positions;
    void update(const float &delta_time);
    void draw(SDL_Renderer *renderer);
};
