#pragma once

#include "SDL2/SDL_rect.h"

namespace aabb {
bool collides(const SDL_FRect &a, const SDL_FRect &b);
}
