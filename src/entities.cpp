#include "entities.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "constants.h"
#include <cmath>
#include <iostream>

Player::Player(float x, float y)
    : position(SDL_FPoint{x, y}), collider(SDL_FRect{x, y, 25.0f, 20.0f}),
      velocity(SDL_FPoint{0, 0}) {};

void Player::update(const float &delta_time) {
    velocity.y += GRAVITY_FORCE * delta_time; // gravity
    if (velocity.y > MAX_VERTICAL_SPEED) {
        velocity.y = MAX_VERTICAL_SPEED;
    }

    position.x += velocity.x * delta_time;
    position.y += velocity.y * delta_time;

    collider.x = position.x + 5;
    collider.y = position.y + 2;

    animation.transformer.x = position.x;
    animation.transformer.y = position.y;

    angle = std::min(90.0f, std::max(-30.0f, velocity.y - 250.0f));

    animation.update(delta_time);
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

MovingScenerio::MovingScenerio(const Texture *texture, float speed, int y) : texture(texture), speed(speed), y(y) {
    positions = std::vector<float>();
    int needed_positions = (LOGICAL_SCREEN_WIDTH / texture->width) + 1;

    while (needed_positions >= 0) {
        positions.push_back(needed_positions * texture->width);
        needed_positions--;
    }
}

void MovingScenerio::update(const float &delta_time) {
    for (float &position : positions) {
        position -= speed * delta_time;

        if (position + texture->width <= 0) {
            position += texture->width * positions.size(); // Puts it after the currently visible background
        }
    }
}

void MovingScenerio::draw(SDL_Renderer* renderer) {
    auto destrect = SDL_Rect{ 0, y, texture->width, texture->height };
    for (const float position : positions) {
        destrect.x = position;
        SDL_RenderCopy(renderer, texture->ptr, NULL, &destrect);
    }
}
