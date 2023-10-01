#include "aabb.h"

bool aabb::collides(const SDL_FRect &a, const SDL_FRect &b) {
    bool x_overlaps = (a.x + a.w) > b.x && a.x < (b.x + b.w);
    bool y_overlaps = (a.y + a.h) > b.y && a.y < (b.y + b.h);

    return x_overlaps && y_overlaps;
}
