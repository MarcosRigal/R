#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

using namespace std;

class GameManager
{
private:
    static GameManager *instance = NULL;

    GameManager();

public:
    static GameManager getInstance();
};

#endif
