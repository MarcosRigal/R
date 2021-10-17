#include "game.h"
using namespace std;

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
