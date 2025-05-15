#ifndef ROOM2_H
#define ROOM2_H

class ScoreManager;  // Forward declaration

namespace Room2 {
    int play_game_scene(unsigned seed,ScoreManager& score_manager);  // Accepts seed from title screen, and score
}

#endif