#pragma once

#include <SDL.h>

struct Clock {
    Clock(Uint32 fps);
    Uint32 target_frame_time;
    Uint32 last_tick_time;
    Uint32 delta;
    void tick();
    void lock_remaining() const;
};
