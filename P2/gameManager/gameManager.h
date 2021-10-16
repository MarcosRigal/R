#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "../user/user.h"
#include "../game/game.h"
using namespace std;

class GameManager
{
private:
    GameManager(){};
    static GameManager *instance;
    vector<User> users_;
    vector<Game> games_;

public:
    static GameManager *getInstance();

    inline vector<User> getUsers() { return users_; }
    inline vector<Game> getGames() { return games_; }

    inline void setUsers(vector<User> users) { users_ = users; }
    inline void setGames(vector<Game> games) { games_ = games; }

    inline void addUser(User user) { users_.push_back(user); }
    inline void addGame(Game game) { games_.push_back(game); }
};

#endif
