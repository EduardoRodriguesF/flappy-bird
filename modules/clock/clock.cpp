#include "clock.h"
#include <iostream>

Clock::Clock(Uint32 fps) : last_tick_time(0), target_frame_time(1000 / fps) {}

void Clock::tick(void) {
    Uint32 tick = SDL_GetTicks();

    delta = (tick - last_tick_time);
    last_tick_time = tick;
}

void Clock::lock_remaining() const {
    if (target_frame_time > delta) {
        SDL_Delay(target_frame_time - delta);
    }
}
