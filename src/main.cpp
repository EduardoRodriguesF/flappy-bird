#include "game.h"

int main() {
    Game game{};

    game.setup();

    while (game.is_running) {
        game.handle_input();
        game.update();
        game.draw();
    }

    return 0;
}
