#pragma once

#include <SDL.h>

class Game {
  public:
    Game();
    ~Game();
    void setup();
    void handle_input();
    void update(Uint32 delta_time);
    void draw();
    bool is_running;

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};
