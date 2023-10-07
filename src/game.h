#pragma once

#include "entities.h"
#include "resource/texture.h"
#include <SDL.h>
#include <list>
#include <memory>

enum class State {
    Start,
    Playing,
    GameOver,
};

struct Game {
  public:
    Game();
    ~Game();
    void setup();
    void load_textures();
    void handle_input();
    void update(const float &delta_time);
    void draw();
    void game_over();
    void new_game();
    bool is_running;
    State state;

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Player player;
    std::list<Pipe> pipes;
    int spawn_timer;
    bool btn_pressed;
    std::unique_ptr<TextureManager> texture_manager;
};
