#include "../include/room1.h"
#include "../include/room2.h"
#include "../include/titlescreen.h"
#include "bn_core.h"
#include "bn_keypad.h"

int main() {
    bn::core::init();
    titlescreen();  // Show title screen first

    while (true) {
        Room1::play_game_scene();
        bn::core::update();
    }

    return 0;
}
