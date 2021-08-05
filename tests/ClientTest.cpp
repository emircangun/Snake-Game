#include "../client/Client.h"
#include "../src/consts.h"
#include <vector>

#include <gtest/gtest.h>

TEST(LoginTest, SuccessfulLogin)
{
    Client user = Client();
    EXPECT_EQ(user.Login("test", "test"), true);
}

TEST(LoginTest, FailedLogin)
{
    Client user = Client();
    EXPECT_EQ(user.Login("test2", "test2"), false);
}

TEST(SignupTest, ExistingUser)
{
    Client user = Client();
    EXPECT_EQ(user.SignUp("test", "test"), false);
}

TEST(AddNewGameTest, AddNewGame)
{
    Client user = Client();
    user.Login("test", "test");

    EXPECT_EQ(user.GetMaxScoreFromDB(), 55);
}

TEST(GetMaximumScoreTest, MaximumScore)
{
    Client user = Client();
    user.Login("test", "test");
    std::vector<Direction> v(20, UP);
    EXPECT_EQ(user.AddGame("test", v, 1), true);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}