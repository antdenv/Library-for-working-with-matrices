#include <string.h>

#include "game.h"

int main(int argc, const char** argv) {
    int map;
    bool second_stage = false;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "--view-armor") == 0) {
            second_stage = true;
        }

        if (strcmp(argv[i], "--map") == 0) {
            map = i;
        }
    }

    Game game(argv[map + 1], second_stage);
    game.run();
    return 0;
}
