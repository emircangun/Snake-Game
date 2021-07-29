#pragma once

#include <string>

class Client
{
private:
    std::string username;
    std::string password;
    int max_score;

public:
    Client();
    ~Client();
    void Login();
    void SignUp();

    std::string GetUsername() const { return username; }
};