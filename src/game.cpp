#include "game.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_error.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_log.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "collision/aabb.h"
#include "constants.h"
#include "entities.h"
#include "resource/sound.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>

Game::Game() : is_running(true), player(0, 0), btn_pressed(false) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        throw std::runtime_error("Failed to initialize SDL");
    }

    if (IMG_Init(IMG_INIT_PNG) < 0) {
        throw std::runtime_error("Failed to initialize IMG");
    }
    Mix_OpenAudio(441000, MIX_DEFAULT_FORMAT, 2, 1024);

    if (Mix_Init(0) < 0) {
        throw std::runtime_error("Failed to initialize Mixer");
    }

    window = SDL_CreateWindow("Flappy bird", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        throw std::runtime_error("Failed to create SDL window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

    background = std::make_unique<MovingScenerio>(texture_manager->get(S_BG_DAY), BG_SPEED, 0);
    floor = std::make_unique<MovingScenerio>(texture_manager->get(S_BASE), SCENE_SPEED, FLOOR_Y);

    points = 0;
}

void Game::load_resources() {
    sound_manager = std::make_unique<SoundManager>("res/audio/");
    texture_manager =
        std::make_unique<TextureManager>(renderer, "res/sprites/");

    sound_manager->load(A_POINT);
    sound_manager->load(A_DIE);
    sound_manager->load(A_WING);
    sound_manager->load(A_HIT);

    texture_manager->load(S_BIRD_MIDFLAP, 34, 24);
    texture_manager->load(S_PIPE, PIPE_WIDTH, PIPE_HEIGHT);
    texture_manager->load(S_BG_DAY, 288, 512);
    texture_manager->load(S_BASE, FLOOR_WIDTH, FLOOR_HEIGHT);
    texture_manager->load(S_BASE, FLOOR_WIDTH, FLOOR_HEIGHT);
    texture_manager->load(S_MESSAGE, S_MESSAGE_W, S_MESSAGE_H);

    for (const std::string_view &name : DIGITS) {
        texture_manager->load(name, 24, 36);
    }
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
    Mix_PlayChannel(-1, sound_manager->get(A_HIT), 0);
}

void Game::update(const float &delta_time) {
    switch (this->state) {
    case State::Playing: {
        background->update(delta_time);
        floor->update(delta_time);

        float scene_acceleration = SCENE_SPEED * delta_time;

        if (spawn_timer <= 0) {
            spawn_timer = PIPE_TIMEOUT_MS;
            int gap_y = std::min(
                std::max(GAP_RADIUS * 2, std::rand() % MAX_GAP_Y),
                LOGICAL_SCREEN_HEIGHT - GAP_RADIUS * 2);
            pipes.push_back(Pipe(gap_y));
        }
        spawn_timer -= delta_time * 1000;

        if (btn_pressed) {
            player.jump();
            Mix_PlayChannel(-1, sound_manager->get(A_WING), 0);
        }

        player.update(delta_time);

        if (player.position.y >= FLOOR_Y) {
            this->game_over();
            break;
        }

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
            break;
        }

        if (!nearest_pipe.passed && nearest_pipe.top_body.x - PIPE_WIDTH / 2 <= player.position.x) {
            points++;
            Mix_PlayChannel(-1, sound_manager->get(A_POINT), 0);
            nearest_pipe.passed = true;
            SDL_Log("Points: %i", points);
        }

        if (nearest_pipe.top_body.x + nearest_pipe.top_body.w < 0) {
            // Pipe out render vision
            pipes.pop_front();
        }

        break;
    }
    case State::GameOver:
        if (player.position.y < FLOOR_Y) {
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
    background->draw(renderer);

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

    floor->draw(renderer);

    auto rect = SDL_Rect{(int)player.position.x, (int)player.position.y,
                         bird_texture->width, bird_texture->height};
    SDL_RenderCopyEx(renderer, bird_texture->ptr, NULL, &rect, player.angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);

    if (state == State::Playing) {
        draw_points();
    } else if (state == State::Start) {
        auto message_texture = texture_manager->get(S_MESSAGE);
        rect.x = LOGICAL_SCREEN_WIDTH / 2 - S_MESSAGE_W / 2;
        rect.y = 52;
        rect.w = message_texture->width;
        rect.h = message_texture->height;

        SDL_RenderCopy(renderer, message_texture->ptr, NULL, &rect);
    } else if (state == State::GameOver) {
        draw_points();
    }

    SDL_RenderPresent(renderer);
}

void Game::draw_points() {
    SDL_Rect destrect { 0, 48, 24, 36 };

    std::vector<int> digits {};

    if (points == 0) {
        digits.push_back(0);
    } else {
        int divisor = 1000;
        int new_digit = 0; 
        do {
            divisor /= 10;
            int new_digit = points / divisor % 10;

            if (digits.size() == 0 && new_digit == 0) {
                continue; // No whole number yet.
            }

            digits.push_back(new_digit);
        } while (divisor > 1);
    }


    destrect.x = (LOGICAL_SCREEN_WIDTH / 2) + (digits.size() * -25 / 2);

    const Texture* texture;
    for (const auto digit : digits) {
        texture = this->texture_manager->get(DIGITS[digit]);
        SDL_RenderCopy(renderer, texture->ptr, NULL, &destrect);

        destrect.x += 25;
    }
}

