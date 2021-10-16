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
