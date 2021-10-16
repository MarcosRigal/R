#include <gtest/gtest.h>
#include "gameManager.h"

using namespace std;

TEST(GameManager, Singleton)
{
    GameManager *gameManager1 = GameManager::getInstance();
    GameManager *gameManager2 = GameManager::getInstance();
    EXPECT_EQ(gameManager1, gameManager2);
}