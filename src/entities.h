#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"

struct Player {
    Player(float x, float y);
    SDL_FPoint position;
    SDL_FPoint velocity;
    SDL_FRect collider;
    void update(const float &delta_time);
    void draw(SDL_Renderer *renderer);
    void jump();
};

struct Pipe {
    Pipe(int gap_y);
    SDL_FRect bottom_body;
    SDL_FRect top_body;
};
