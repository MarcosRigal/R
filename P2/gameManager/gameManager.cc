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
    else if (numberOfGames_ > 0 && numberOfGames_ < 11)
    {
        Game game = games_[numberOfGames_ - 1];
        if (game.addPlayer(socketPlayer))
        {
            games_.pop_back();
            games_.push_back(game);
            return 1;
        }
        else if (numberOfGames_ + 1 < 11)
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
        if (strcmp(users_[i].getUserName(), name) == 0)
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
        if (strcmp(users_[i].getUserName(), name) == 0)
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
        if ((strcmp(users_[i].getUserName(), name) == 0) && (users_[i].getUserSocket() == -1))
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
        if ((strcmp(users_[i].getUserName(), name) == 0) && (users_[i].getUserSocket() == -1))
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
        if ((strcmp(users_[i].getUserPassword(), password) == 0) && (users_[i].getUserSocket() == userSocket))
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
        if ((strcmp(users_[i].getUserPassword(), password) == 0) && (users_[i].getUserSocket() == userSocket))
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
                numberOfGames_--;
                return true;
            }
            else if (it->getSocketPlayer2() == userSocket)
            {
                games_.erase(it);
                numberOfGames_--;
                return true;
            }
        }
    }
    return false;
}

int GameManager::getScore(int userSocket)
{
    for (int i = 0; i < (int)games_.size(); i++)
    {
        if (games_[i].getNumberOfPlayers() == 2)
        {
            if (games_[i].getSocketPlayer1() == userSocket)
            {
                return games_[i].getScorePlayer1();
            }
            else if (games_[i].getSocketPlayer2() == userSocket)
            {
                return games_[i].getScorePlayer2();
            }
        }
    }

    return -1;
}

Game GameManager::getGame(int userSocket)
{
    for (int i = 0; i < (int)games_.size(); i++)
    {
        if (games_[i].getNumberOfPlayers() == 2)
        {
            if (games_[i].getSocketPlayer1() == userSocket)
            {
                return games_[i];
            }
            else if (games_[i].getSocketPlayer2() == userSocket)
            {
                return games_[i];
            }
        }
    }
    Game fakeGame;
    return fakeGame;
}

char *GameManager::getName(int userSocket)
{
    for (int i = 0; i < (int)users_.size(); i++)
    {
        if (users_[i].getUserSocket() == userSocket)
        {
            return users_[i].getUserName();
        }
    }
    return nullptr;
}

int GameManager::findOcurrences(int userSocket, const char letter)
{
    for (int i = 0; i < (int)games_.size(); i++)
    {
        if (games_[i].getNumberOfPlayers() == 2)
        {
            if (games_[i].getSocketPlayer1() == userSocket)
            {
                return games_[i].findOcurrences(letter);
            }
            else if (games_[i].getSocketPlayer2() == userSocket)
            {
                return games_[i].findOcurrences(letter);
            }
        }
    }
    return -1;
}

void GameManager::addPlayerScore(int userSocket, int multiplier)
{
    for (int i = 0; i < (int)games_.size(); i++)
    {
        if (games_[i].getNumberOfPlayers() == 2)
        {
            if (games_[i].getSocketPlayer1() == userSocket)
            {
                return games_[i].setScorePlayer1(50 * multiplier);
            }
            else if (games_[i].getSocketPlayer2() == userSocket)
            {
                games_[i].setScorePlayer2(50 * multiplier);
            }
        }
    }
}