#ifndef GAME_H
#define GAME_H

using namespace std;

class Game
{
private:
    int player1_;
    int player2_;
    int scorePlayer1_;
    int scorePlayer2_;

public:
    inline int getPlayer1() { return player1_; }
    inline int getPlayer2() { return player2_; }
    inline int getScorePlayer1() { return scorePlayer1_; }
    inline int getScorePlayer2() { return scorePlayer2_; }

    inline void setPlayer1(int player1) { player1_ = player1; }
    inline void setPlayer2(int player2) { player2_ = player2; }
    inline void setScorePlayer1(int scorePlayer1) { scorePlayer1_ = scorePlayer1; }
    inline void setScorePlayer2(int scorePlayer2) { scorePlayer2_ = scorePlayer2; }
};

#endif