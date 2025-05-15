#ifndef ROOM1_H
#define ROOM1_H

class ScoreManager;  // Forward declaration

namespace Room1 {
    int play_game_scene(unsigned seed,ScoreManager& score_manager);  // Accepts seed from title screen, and score
}

#endif // ROOM1_H
