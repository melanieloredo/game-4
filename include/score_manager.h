#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

class ScoreManager {
public:
    // Reset only current score (not highscore)
    void reset_current_score();

    // Optional: reset both scores if ever needed
    void reset_all();

    void add_points(int points);
    void draw_score(int x, int y);
    int current_score() const;
    
    //highscore
    void update_highscore();
    int get_highscore() const;

private:
    int _score = 0;
    int _highscore = 0;  // session highscore
};

#endif // SCORE_MANAGER_H
