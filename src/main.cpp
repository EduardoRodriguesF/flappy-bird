#include "clock/clock.h"
#include "game.h"
#include <memory>

int main() {
    Game game{};
    auto clock = std::make_unique<Clock>(60);

    game.setup();

    while (game.is_running) {
        game.handle_input();
        game.update(clock->delta / 1000.0f);
        game.draw();

        clock->tick();
        clock->lock_remaining();
    }

    return 0;
}
