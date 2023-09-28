#pragma once

#include "entities.h"
#include <SDL.h>

class Game {
  public:
    Game();
    ~Game();
    void setup();
    void handle_input();
    void update(const float &delta_time);
    void draw();
    bool is_running;

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Player player;
};
