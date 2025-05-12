#include "../include/room1.h"
#include "../include/room2.h"
#include "../include/titlescreen.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include <bn_random.h>

int main() {
    bn::core::init();

    bn::random random;
    int roomNum = random.get_int(2);

    while (true) {
        unsigned seed = titlescreen();

        while (bn::keypad::any_held()) {
            bn::core::update();
        }

        bool keepGoing = true;
        int gameCode;
        while (keepGoing) {
            // select room based on random int
            switch (roomNum) {
                case 0: 
                    gameCode = Room1::play_game_scene(seed);
                    break;
                case 1:
                    gameCode = Room2::play_game_scene(seed + 1);
                    break;
                default:
                    gameCode = Room1::play_game_scene(seed);
                    break;
            }
            // user action translated to game action
            if (gameCode == 0) break; // title screen / quit game
            // else if (gameCode == 2) go to game over screen
            roomNum = random.get_int(2);
            bn::core::update();
        }
    }

    return 0;
}