#include "../include/room1.h"
#include "../include/room2.h"
#include "../include/room3.h"
#include "../include/titlescreen.h"

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_random.h"

int main() {
    bn::core::init();

    while (true) {
        unsigned seed = titlescreen();

        while (bn::keypad::any_held()) {
            bn::core::update();
        }

        bn::random random;
        int lastRoom = -1;
        unsigned currentSeed = seed;

        while (true) {
            int roomNum = random.get_int(3);

            // Ensure a different room than the last
            if (roomNum == lastRoom) {
                currentSeed += 17;  // Arbitrary offset to change layout
                roomNum = (roomNum + 1) % 3;  // Simple cycle fallback
            }

            switch (roomNum) {
                case 0:
                    Room1::play_game_scene(currentSeed);
                    break;
                case 1:
                    Room2::play_game_scene(currentSeed + 1);
                    break;
                case 2:
                    Room3::play_game_scene(currentSeed + 2);
                    break;
                default:
                    break;
            }

            lastRoom = roomNum;

            if (bn::keypad::select_held()) {
                break;
            }

            bn::core::update();
        }
    }

    return 0;
}
