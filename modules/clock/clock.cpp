#include "clock.h"

Clock::Clock(Uint32 fps) {
    this->target_frame_time = fps / 1000.0f;
}

void Clock::tick(void) {
    Uint32 tick = SDL_GetTicks();

    delta = (tick - last_tick_time) * target_frame_time;
    last_tick_time = tick;
}

void Clock::lock_remaining() const {
    if (target_frame_time <= delta) {
        return;
    }

    SDL_Delay(target_frame_time - delta);
}
