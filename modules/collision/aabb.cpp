#include "aabb.h"

bool aabb::collides(const SDL_FRect &a, const SDL_FRect &b) {
    bool x_overlaps = a.x + a.w >= b.x && b.x + b.w >= a.x;
    bool y_overlaps = a.y + a.h >= b.y && b.y + b.h >= a.y;

    return x_overlaps && y_overlaps;
}
