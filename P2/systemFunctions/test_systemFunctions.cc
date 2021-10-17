#include <gtest/gtest.h>
#include "systemFunctions.h"

using namespace std;

TEST(System, loadSystem)
{
  loadSystem();
  GameManager *gameManager = GameManager::getInstance();
  EXPECT_EQ(strcmp(gameManager->getUsers()[0].getUserName(), "marcos"), 0);
  EXPECT_EQ(strcmp(gameManager->getUsers()[1].getUserName(), "paco"), 0);
  EXPECT_EQ(strcmp(gameManager->getUsers()[0].getUserPassword(), "1234"), 0);
  EXPECT_EQ(strcmp(gameManager->getUsers()[1].getUserPassword(), "1234"), 0);
}