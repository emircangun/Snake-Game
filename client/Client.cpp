#include "Client.h"
#include "connections.h"
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Client::Client()
{
}

Client::~Client()
{
}

// existing user
bool Client::Login(std::string username, std::string password)
{
    std::string login_url = std::string(API_URL) + std::string("login");
    json json_data;
    json_data["username"] = username;
    json_data["password"] = password;

    cpr::Response r = cpr::Post(cpr::Url{login_url},
                                cpr::Body{json_data.dump()},
                                cpr::Header{{"Content-Type", "application/json"}});

    std::cout << std::endl << r.text << std::endl;

    if (r.text == "Succeed")
    {
        this->username = username;
        this->max_score = GetMaxScoreFromDB();
        return true;
    }
    else
    {
        return false;
    }
}

// new user
bool Client::SignUp()
{
    std::string signup_url = std::string(API_URL) + std::string("signup");
    json json_data;
    json_data["username"] = username;
    json_data["password"] = password;

    cpr::Response r = cpr::Post(cpr::Url{signup_url},
                                cpr::Body{json_data.dump()},
                                cpr::Header{{"Content-Type", "application/json"}});

    std::cout << r.text << std::endl;

    if (r.text == "Succeed")
    {
        this->username = username;
        this->max_score = GetMaxScoreFromDB();
        return true;
    }
    else
    {
        return false;
    }
}

bool Client::AddGame(std::string password, std::vector<Direction> direction_history, int score)
{
    std::string add_game_url = std::string(API_URL) + this->username + std::string("/add_game");

    json json_data;
    json_data["password"] = password;
    json_data["score"] = score;
    json_data["direction_history"] = direction_history;
    cpr::Response r = cpr::Post(cpr::Url{add_game_url},
                                cpr::Body{json_data.dump()},
                                cpr::Header{{"Content-Type", "application/json"}});

    if (r.text == "Failed")
        return false;
    else
        return true;
}

int Client::GetMaxScoreFromDB()
{
    std::string get_game_url = std::string(API_URL) + this->username + std::string("/max_score");
    cpr::Response r = cpr::Get(cpr::Url{get_game_url});
    
    json json_data;
    try {
        json_data = json::parse(r.text);
    } catch (json::parse_error& e) {
        return 0;
    }

    return json_data["max_score"];
}