#include "game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_log.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "SDL2_image/SDL_image.h"
#include "collision/aabb.h"
#include "constants.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

Game::Game() : is_running(true), player(0, 0), btn_pressed(false) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL");
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        throw std::runtime_error("Failed to initialize IMG");
    }

    window = SDL_CreateWindow("Flappy bird", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        throw std::runtime_error("Failed to create SDL window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error("Failed to create SDL window");
    }

    SDL_RenderSetLogicalSize(renderer, LOGICAL_SCREEN_WIDTH,
                             LOGICAL_SCREEN_HEIGHT);
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::setup() {
    player = Player(64.0f, LOGICAL_SCREEN_HEIGHT / 2);
    pipes = std::list<Pipe>({Pipe(LOGICAL_SCREEN_HEIGHT / 2)});
    spawn_timer = PIPE_TIMEOUT_MS;
}

void Game::load_textures() {
    texture_manager =
        std::make_unique<TextureManager>(renderer, "res/sprites/");

    texture_manager->load(S_BIRD_MIDFLAP, 34, 24);
    texture_manager->load(S_PIPE, 52, 320);
}

void Game::handle_input() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            this->is_running = false;
            break;
        case SDL_KEYDOWN:
            btn_pressed = e.key.keysym.sym == SDLK_SPACE;
            break;
        }
        if (e.type == SDL_QUIT) {
            this->is_running = false;
        }
    }
}

void Game::new_game() {
    this->setup();
    state = State::Playing;
}

void Game::game_over() {
    player.velocity.y = 0;
    state = State::GameOver;
}

void Game::update(const float &delta_time) {
    switch (this->state) {
    case State::Playing: {
        float scene_acceleration = SCENE_SPEED * delta_time;

        if (spawn_timer <= 0) {
            spawn_timer = PIPE_TIMEOUT_MS;
            int gap_y = std::min(
                std::max(GAP_RADIUS * 2, std::rand() % LOGICAL_SCREEN_HEIGHT),
                LOGICAL_SCREEN_HEIGHT - GAP_RADIUS * 2);
            pipes.push_back(Pipe(gap_y));
        }
        spawn_timer -= delta_time * 1000;

        if (btn_pressed) {
            player.jump();
        }

        player.update(delta_time);

        for (auto &pipe : this->pipes) {
            pipe.top_body.x -= scene_acceleration;
            pipe.bottom_body.x -= scene_acceleration;
        }

        Pipe &nearest_pipe = pipes.front();

        bool top_collides =
            aabb::collides(player.collider, nearest_pipe.top_body);
        bool bottom_collides =
            aabb::collides(player.collider, nearest_pipe.bottom_body);

        if (top_collides || bottom_collides) {
            this->game_over();
        }

        if (nearest_pipe.top_body.x + nearest_pipe.top_body.w < 0) {
            // Pipe out render vision
            pipes.pop_front();
        }

        break;
    }
    case State::GameOver:
        if (player.position.y < LOGICAL_SCREEN_HEIGHT - 16.0f) {
            player.update(delta_time);
        } else if (btn_pressed) {
            this->new_game();
        }
        break;
    default:
        if (btn_pressed) {
            this->new_game();
        }
        break;
    }

    btn_pressed = false;
}

void Game::draw() {
    auto bird_texture = texture_manager->get(S_BIRD_MIDFLAP);
    auto pipe_texture = texture_manager->get(S_PIPE);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    auto render_rect = SDL_FRect {
        0.0f, 0.0f,
        static_cast<float>(pipe_texture->width), static_cast<float>(pipe_texture->height),
    };
    for (auto &pipe : this->pipes) {
        render_rect.x = pipe.top_body.x;
        render_rect.y = pipe.top_body.y - pipe_texture->height + pipe.top_body.h;
        SDL_RenderCopyExF(renderer, pipe_texture->ptr, NULL, &render_rect, 0.0, NULL, SDL_RendererFlip::SDL_FLIP_VERTICAL);

        render_rect.x = pipe.bottom_body.x;
        render_rect.y = pipe.bottom_body.y;
        SDL_RenderCopyF(renderer, pipe_texture->ptr, NULL, &render_rect);
    }

    player.draw(renderer);

    auto rect = SDL_Rect{(int)player.position.x, (int)player.position.y,
                         bird_texture->width, bird_texture->height};
    SDL_RenderCopyEx(renderer, bird_texture->ptr, NULL, &rect, player.velocity.y * 30.0, NULL, SDL_RendererFlip::SDL_FLIP_NONE);

    SDL_RenderPresent(renderer);
}
