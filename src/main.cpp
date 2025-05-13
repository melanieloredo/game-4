#include "../include/room1.h"
#include "../include/room2.h"
#include "../include/room3.h"
#include "../include/titlescreen.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include <bn_random.h>

int main() {
    bn::core::init();

    bn::random random;
    int roomNum = random.get_int(3); // 0, 1, or 2

    while (true) {
        unsigned seed = titlescreen();

        while (bn::keypad::any_held()) {
            bn::core::update();
        }

        bool keepGoing = true;
        while (keepGoing) {
            switch (roomNum) {
                case 0: 
                    Room1::play_game_scene(seed);
                    break;
                case 1:
                    Room2::play_game_scene(seed + 1);
                    break;
                case 2:
                    Room3::play_game_scene(seed + 2);
                    break;
                default:
                    Room1::play_game_scene(seed);
                    break;
            }

            roomNum = random.get_int(3);
            bn::core::update();
        }
    }

    return 0;
}
