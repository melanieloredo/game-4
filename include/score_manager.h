#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

class ScoreManager {
public:
    void reset();
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
