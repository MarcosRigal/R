#include <gtest/gtest.h>
#include "user.h"

using namespace std;

TEST(User, Socket)
{
    User user;
    user.setUserSocket(5);
    EXPECT_EQ(user.getUserSocket(), 5);
}

TEST(User, Name)
{
    User user;
    user.setUserName("Marcos");
    EXPECT_EQ(strcmp(user.getUserName(), "Marcos"), 0);
}

TEST(User, Password)
{
    User user;
    user.setUserPassword("1234");
    EXPECT_EQ(strcmp(user.getUserPassword(), "1234"), 0);
}

TEST(User, Status)
{
    User user;
    EXPECT_TRUE(user.getUserStatus());
}