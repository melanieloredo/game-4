#ifndef ROOM3_H
#define ROOM3_H

class ScoreManager;  // Forward declaration

namespace Room3 {
    int play_game_scene(unsigned seed,ScoreManager& score_manager);  // Accepts seed from title screen, and score
}

#endif