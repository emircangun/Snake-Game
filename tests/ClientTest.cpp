#include "../client/Client.h"
#include <iostream>

int main()
{
    Client test_user = Client();
    int score = -1;
    try {
        test_user.Login();
        score = test_user.GetMaxScoreFromDB();
    } catch(const char* err) {
        std::cout << err << std::endl;
    }
    
    std::cout << score << std::endl;

    return 0;
}