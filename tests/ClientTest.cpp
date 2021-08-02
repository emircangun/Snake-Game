#include "../client/Client.h"
#include <iostream>

int main()
{
    Client test_user = Client();
    try {
        test_user.Login();
        test_user.GetMaxScoreFromDB();
    } catch(const char* err) {
        std::cout << err << std::endl;
    }
    

    return 0;
}