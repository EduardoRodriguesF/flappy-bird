#include "entities.h"
#include "constants.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include <iostream>

Player::Player(float x, float y)
    : position(SDL_FPoint{x, y}), collider(SDL_FRect{x, y, 16.0f, 16.0f}),
      velocity(SDL_FPoint{0, 0}){};

void Player::update(const float &delta_time) {
    velocity.y += GRAVITY_FORCE * delta_time; // gravity
    if (velocity.y > MAX_VERTICAL_SPEED) {
        velocity.y = MAX_VERTICAL_SPEED;
    }

    position.x += velocity.x;
    position.y += velocity.y;

    collider.x = position.x;
    collider.y = position.y;
}

void Player::jump() { this->velocity.y = -JUMP_FORCE; }

void Player::draw(SDL_Renderer *renderer) {
    SDL_RenderDrawRectF(renderer, &this->collider);
}

Pipe::Pipe(int gap_y) {
    float bottom_start_y = gap_y + GAP_RADIUS;

    float top_height = gap_y - GAP_RADIUS;
    float bottom_height = LOGICAL_SCREEN_HEIGHT - bottom_start_y;

    float start_x = static_cast<float>(LOGICAL_SCREEN_WIDTH);

    this->top_body = SDL_FRect {start_x, 0.0f, PIPE_WIDTH, top_height};
    this->bottom_body = SDL_FRect {start_x, bottom_start_y, PIPE_WIDTH, bottom_height};
}
