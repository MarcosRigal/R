#include "game.h"

bool Game::addPlayer(int socketPlayer)
{
    if (numberOfPlayers_ == 0)
    {
        setSocketPlayer1(socketPlayer);
        numberOfPlayers_++;
        return true;
    }
    else if (numberOfPlayers_ == 1)
    {
        setSocketPlayer2(socketPlayer);
        numberOfPlayers_++;
        return true;
    }
    return false;
}

using namespace std;