#pragma once

#include <string>
#include <vector>
#include "../src/consts.h"

class Client
{
private:
    std::string username;
    int max_score;

public:
    Client();
    ~Client();
    bool Login(std::string, std::string);
    bool SignUp(std::string, std::string);
    bool AddGame(std::string, std::vector<Direction>, int);
    int GetMaxScoreFromDB();

    std::string GetUsername() const { return username; }
    int GetMaxScore()         const { return max_score; }
};