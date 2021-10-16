#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

using namespace std;

class GameManager
{
private:
    GameManager();
    static GameManager *instance; // GameManager instance

public:
    static GameManager *getInstance();
};

#endif
