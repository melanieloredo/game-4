#include "../include/room1.h"
#include "../include/room2.h"
#include "../include/room3.h"
#include "../include/titlescreen.h"
#include "../include/score_manager.h"  // include ScoreManager

#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_random.h"

int main() {
    bn::core::init();

    ScoreManager score_manager;

    while (true) {
        unsigned seed = titlescreen(score_manager);

        while (bn::keypad::any_held()) {
            bn::core::update();
        }

        // Reset only the current score at the start of gameplay
        score_manager.reset_current_score();

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
                    Room1::play_game_scene(currentSeed, score_manager);
                    break;
                case 1:
                    Room2::play_game_scene(currentSeed + 1, score_manager);
                    break;
                case 2:
                    Room3::play_game_scene(currentSeed + 2, score_manager);
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
         // finalize the run before going to title screen
        score_manager.update_highscore();
    }

    return 0;
}
