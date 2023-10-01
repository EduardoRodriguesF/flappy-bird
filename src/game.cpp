#include "game.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_log.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "collision/aabb.h"
#include "constants.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

Game::Game() : is_running(true), player(0, 0) {
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
    player.position = SDL_FPoint{64.0f, 0.0f};
    pipes.push_back(Pipe(100));
    spawn_timer = PIPE_TIMEOUT_MS;
}

void Game::handle_input() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_QUIT:
            this->is_running = false;
            break;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_SPACE) {
                if (state == State::Playing) {
                    player.jump();
                }
            }

            break;
        }
        if (e.type == SDL_QUIT) {
            this->is_running = false;
        }
    }
}

void Game::game_over() {
    player.velocity.y = 0;
    state = State::GameOver;
}

void Game::update(const float &delta_time) {
    switch (this->state) {
    case State::Playing: {
        if (spawn_timer <= 0) {
            spawn_timer = PIPE_TIMEOUT_MS;
            int gap_y = std::rand() % LOGICAL_SCREEN_HEIGHT;
            pipes.push_back(Pipe(gap_y));
        }
        spawn_timer -= delta_time * 1000;

        player.update(delta_time);

        for (auto &pipe : this->pipes) {
            pipe.top_body.x -= 38.0f * delta_time;
            pipe.bottom_body.x -= 38.0f * delta_time;
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
        }
    }
}

void Game::draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (auto &pipe : this->pipes) {
        SDL_RenderDrawRectF(renderer, &pipe.top_body);
        SDL_RenderDrawRectF(renderer, &pipe.bottom_body);
    }

    player.draw(renderer);

    SDL_RenderPresent(renderer);
}
