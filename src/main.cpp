#include "../include/room1.h"
#include "../include/titlescreen.h"
#include "bn_core.h"
#include "bn_keypad.h"

int main() {
    bn::core::init();

    while (true) {
        unsigned seed = titlescreen();  // player presses Start here

        // 🔒 Wait until all keys are released to prevent auto-skipping
        while (bn::keypad::any_held()) {
            bn::core::update();
        }

        Room1::play_game_scene(seed);   // only runs after keys are released
        bn::core::update();
    }

    return 0;
}
