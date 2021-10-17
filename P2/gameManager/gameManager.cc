#include "gameManager.h"
#include "stdio.h"

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

int GameManager::matchUser(int socketPlayer)
{
    if (numberOfGames_ == 0)
    {
        Game game;
        game.addPlayer(socketPlayer);
        addGame(game);
        return 0;
    }
    if (numberOfGames_ > 0 && numberOfGames_ < 11)
    {
        Game game = games_[numberOfGames_ - 1];
        if (game.addPlayer(socketPlayer))
        {
            games_.pop_back();
            games_.push_back(game);
            return 1;
        }
        else
        {
            Game game;
            game.addPlayer(socketPlayer);
            addGame(game);
            return 0;
        }
    }
    return -1;
}

bool GameManager::nameExist(char *name)
{
    for (int i = 0; i < (int)users_.size(); i++)
    {
        if (strtok(users_[i].getUserName(), name) == 0)
        {
            return true;
        }
    }
    return false;
}

bool GameManager::nameExist(const char *name)
{
    for (int i = 0; i < (int)users_.size(); i++)
    {
        if (strtok(users_[i].getUserName(), name) == 0)
        {
            return true;
        }
    }
    return false;
}

bool GameManager::logUser(int userSocket, char *name)
{
    for (int i = 0; i < (int)users_.size(); i++)
    {
        if ((strtok(users_[i].getUserName(), name) == 0) && (users_[i].getUserSocket() == -1))
        {
            users_[i].setUserSocket(userSocket);
            return true;
        }
    }
    return false;
}

bool GameManager::logUser(int userSocket, const char *name)
{
    for (int i = 0; i < (int)users_.size(); i++)
    {
        if ((strtok(users_[i].getUserName(), name) == 0) && (users_[i].getUserSocket() == -1))
        {
            users_[i].setUserSocket(userSocket);
            return true;
        }
    }
    return false;
}

bool GameManager::unlogUser(int userSocket)
{
    for (int i = 0; i < (int)users_.size(); i++)
    {
        if (users_[i].getUserSocket() == userSocket)
        {
            users_[i].setUserSocket(-1);
            return true;
        }
    }
    return false;
}

bool GameManager::checkPassword(int userSocket, char *password)
{
    for (int i = 0; i < (int)users_.size(); i++)
    {
        if ((strtok(users_[i].getUserPassword(), password) == 0) && (users_[i].getUserSocket() == userSocket))
        {
            return true;
        }
    }
    return false;
}

bool GameManager::checkPassword(int userSocket, const char *password)
{
    for (int i = 0; i < (int)users_.size(); i++)
    {
        if ((strtok(users_[i].getUserPassword(), password) == 0) && (users_[i].getUserSocket() == userSocket))
        {
            return true;
        }
    }
    return false;
}

bool GameManager::deleteGame(int userSocket)
{
    for (std::vector<Game>::iterator it = games_.begin(); it != games_.end(); it++)
    {
        {
            if (it->getSocketPlayer1() == userSocket)
            {
                games_.erase(it);
                return true;
            }
            else if (it->getSocketPlayer2() == userSocket)
            {
                games_.erase(it);
                return true;
            }
        }
    }
    return false;
}