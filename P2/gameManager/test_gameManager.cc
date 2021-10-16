#include <gtest/gtest.h>
#include "gameManager.h"

using namespace std;

TEST(GameManager, Singleton)
{
    GameManager *gameManager1 = GameManager::getInstance();
    GameManager *gameManager2 = GameManager::getInstance();
    EXPECT_EQ(gameManager1, gameManager2);
}

TEST(GameManager, UsersVector)
{
    GameManager *gameManager = GameManager::getInstance();

    User user1;
    user1.setUserName("Marcos");
    user1.setUserPassword("1234");
    gameManager->addUser(user1);

    User user2;
    user2.setUserName("Salcedo");
    user2.setUserPassword("1234");
    gameManager->addUser(user2);

    EXPECT_EQ(strcmp(gameManager->getUsers()[0].getUserName(), "Marcos"), 0);
    EXPECT_EQ(strcmp(gameManager->getUsers()[1].getUserName(), "Salcedo"), 0);
}

TEST(GameManager, GamesVector)
{
    GameManager *gameManager = GameManager::getInstance();

    Game game1;
    game1.setSocketPlayer1(1);
    gameManager->addGame(game1);

    Game game2;
    game2.setSocketPlayer2(2);
    gameManager->addGame(game2);

    EXPECT_EQ(gameManager->getGames()[0].getSocketPlayer1(), 1);
    EXPECT_EQ(gameManager->getGames()[1].getSocketPlayer2(), 2);
}

TEST(GameManager, numberOfGames)
{
    GameManager *gameManager = GameManager::getInstance();

    EXPECT_EQ(gameManager->getNumberOfGames(), 0);
    gameManager->setNumberOfGames(1);
    EXPECT_EQ(gameManager->getNumberOfGames(), 1);
}