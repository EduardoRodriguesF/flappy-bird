#include "entities.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "constants.h"
#include <iostream>

Player::Player(float x, float y)
    : position(SDL_FPoint{x, y}), collider(SDL_FRect{x, y, 25.0f, 20.0f}),
      velocity(SDL_FPoint{0, 0}){};

void Player::update(const float &delta_time) {
    velocity.y += GRAVITY_FORCE * delta_time; // gravity
    if (velocity.y > MAX_VERTICAL_SPEED) {
        velocity.y = MAX_VERTICAL_SPEED;
    }

    position.x += velocity.x * delta_time;
    position.y += velocity.y * delta_time;

    collider.x = position.x + 5;
    collider.y = position.y + 2;

    angle = std::min(45.0, std::max(-45.0, velocity.y * 50.0));
}

void Player::jump() { this->velocity.y = -JUMP_FORCE; }

void Player::draw_collider(SDL_Renderer *renderer) {
    SDL_RenderDrawRectF(renderer, &this->collider);
}

Pipe::Pipe(int gap_y) {
    float bottom_start_y = gap_y + GAP_RADIUS;

    float top_height = gap_y - GAP_RADIUS;
    float bottom_height = LOGICAL_SCREEN_HEIGHT - bottom_start_y;

    float start_x = static_cast<float>(LOGICAL_SCREEN_WIDTH);

    this->top_body = SDL_FRect{start_x, 0.0f, PIPE_WIDTH, top_height};
    this->bottom_body =
        SDL_FRect{start_x, bottom_start_y, PIPE_WIDTH, bottom_height};
}

void Background::update(const float &delta_time) {
    for (float &position : positions) {
        position -= BG_SPEED * delta_time;

        if (position + texture->width <= 0) {
            position += texture->width * 2; // Puts it after the currently visible background
        }
    }
}

void Background::draw(SDL_Renderer* renderer) {
    auto destrect = SDL_Rect{ 0, 0, texture->width, texture->height };
    for (const float position : positions) {
        destrect.x = position;
        SDL_RenderCopy(renderer, texture->ptr, NULL, &destrect);
    }
}
