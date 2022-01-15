#ifndef SCORE
#define SCORE

#include <iostream>
class Score
{

protected:
    Score()
    {
    }

    int score = 0;
    int lives = 3;
    static Score* score_;


public:


    Score(Score& other) = delete;
    static Score* GetInstance();

    void addToScore(int toAdd)
    {
        score += toAdd;
    }

    void losescore(int toLose) {
        score -= toLose;
    }
    void loselife() {
        lives--;
    }

    void setlife() {
        lives = 3;
    }

    int getScore() {
        return score;
    }

    int getlives() {
        return lives;
    }
};
#endif
