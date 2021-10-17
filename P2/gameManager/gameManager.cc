#include "gameManager.h"

using namespace std;

GameManager *GameManager::instance = nullptr;

GameManager *GameManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameManager();
    }
    return instance;
}

bool GameManager::addGame(Game game)
{
    if (numberOfGames_ < 10)
    {
        games_.push_back(game);
        numberOfGames_++;
        return true;
    }
    return false;
}

int GameManager::findPair(int socketPlayer)
{
    for (int i = 0; i < (int)games_.size(); i++)
    {
        if (games_[i].getNumberOfPlayers() == 2)
        {
            if (games_[i].getSocketPlayer1() == socketPlayer)
            {
                return games_[i].getSocketPlayer2();
            }
            else if (games_[i].getSocketPlayer2() == socketPlayer)
            {
                return games_[i].getSocketPlayer1();
            }
        }
    }

    return -1;
}

bool GameManager::matchUser(int socketPlayer)
{
    if (numberOfGames_ == 0)
    {
        Game game;
        game.addPlayer(socketPlayer);
        addGame(game);
        return false;
    }
    if (numberOfGames_ > 0 && numberOfGames_ < 11)
    {
        Game game = games_[numberOfGames_ - 1];
        if (game.addPlayer(socketPlayer))
        {
            games_.pop_back();
            games_.push_back(game);
            return true;
        }
        else
        {
            Game game;
            game.addPlayer(socketPlayer);
            addGame(game);
            return false;
        }
    }
    return false;
}