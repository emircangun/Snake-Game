#pragma once

#include <string>

class Client
{
private:
    std::string username;
    int max_score;

public:
    Client();
    ~Client();
    void Login();
    void SignUp();
    int GetMaxScoreFromDB();

    std::string GetUsername() const { return username; }
    int GetMaxScore()         const { return max_score; }
};