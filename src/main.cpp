#include "../include/room1.h"
#include "../include/room2.h"
#include "../include/titlescreen.h"
#include "bn_core.h"
#include "bn_keypad.h"

int main() {
    bn::core::init();

    while (true) {
        unsigned seed = titlescreen();

        while (bn::keypad::any_held()) {
            bn::core::update();
        }

        Room1::play_game_scene(seed);
        Room2::play_game_scene(seed + 1); // transition to Room2
    }

    return 0;
}