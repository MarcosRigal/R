#include <gtest/gtest.h>
#include "game.h"

using namespace std;

TEST(Game, SocketPlayer1)
{
    Game game;
    game.setSocketPlayer1(1);
    EXPECT_EQ(game.getSocketPlayer1(), 1);
}

TEST(Game, SocketPlayer2)
{
    Game game;
    game.setSocketPlayer2(2);
    EXPECT_EQ(game.getSocketPlayer2(), 2);
}

TEST(Game, ScorePlayer1)
{
    Game game;
    EXPECT_EQ(game.getScorePlayer1(), 0);
}

TEST(Game, ScorePlayer2)
{
    Game game;
    EXPECT_EQ(game.getScorePlayer2(), 0);
}

TEST(Game, ScorePlayer2)
{
    Game game;
    EXPECT_EQ(game.getNumberOfPlayers(), 0);
}