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

    gameManager->matchUser(1);
    gameManager->matchUser(2);
    gameManager->matchUser(3);
    gameManager->matchUser(4);

    EXPECT_EQ(gameManager->getGames()[0].getSocketPlayer1(), 1);
    EXPECT_EQ(gameManager->getGames()[0].getSocketPlayer2(), 2);
    EXPECT_EQ(gameManager->getGames()[1].getSocketPlayer1(), 3);
    EXPECT_EQ(gameManager->getGames()[1].getSocketPlayer2(), 4);

    EXPECT_EQ(gameManager->findPair(1), 2);
    EXPECT_EQ(gameManager->findPair(2), 1);

    EXPECT_EQ(gameManager->findPair(3), 4);
    EXPECT_EQ(gameManager->findPair(4), 3);
}

TEST(GameManager, numberOfGames)
{
    GameManager *gameManager = GameManager::getInstance();

    EXPECT_EQ(gameManager->getNumberOfGames(), 2);
}