#ifndef GAME_H
#define GAME_H

using namespace std;

#include "../refran/refran.h"

class Game
{
private:
    int socketPlayer1_;
    int socketPlayer2_;

    int scorePlayer1_;
    int scorePlayer2_;

    int numberOfPlayers_;

    Refran refran_;

public:
    Game()
    {
        scorePlayer1_ = 0;
        scorePlayer2_ = 0;
        numberOfPlayers_ = 0;
    }

    inline int getSocketPlayer1() { return socketPlayer1_; }
    inline int getSocketPlayer2() { return socketPlayer2_; }

    int getScore(int sockerPlayer);

    inline int getScorePlayer1() { return scorePlayer1_; }
    inline int getScorePlayer2() { return scorePlayer2_; }

    inline int getNumberOfPlayers() { return numberOfPlayers_; }

    inline Refran getRefran() { return refran_; }

    inline void setSocketPlayer1(int socketPlayer1) { socketPlayer1_ = socketPlayer1; }
    inline void setSocketPlayer2(int socketPlayer2) { socketPlayer2_ = socketPlayer2; }

    inline void setScorePlayer1(int scorePlayer1) { scorePlayer1_ = scorePlayer1; }
    inline void setScorePlayer2(int scorePlayer2) { scorePlayer2_ = scorePlayer2; }

    inline void setNumberOfPlayers(int numberOfPlayers) { numberOfPlayers_ = numberOfPlayers; }

    inline void setRefran(Refran refran) { refran_ = refran; }

    bool addPlayer(int socketPlayer);
    inline int findOcurrences(const char letter) { return refran_.findOcurrences(letter); }
};

#endif