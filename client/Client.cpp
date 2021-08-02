#include "Client.h"
#include "connections.h"
#include <iostream>
#include <string>
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
void Client::Login()
{
    std::string username;
    std::string password;

    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    std::string login_url = std::string(BASE_URL) + std::string("login");
    json json_data;
    json_data["username"] = username;
    json_data["password"] = password;

    cpr::Response r = cpr::Post(cpr::Url{login_url},
                                cpr::Body{json_data.dump()},
                                cpr::Header{{"Content-Type", "application/json"}});

    if (r.text == "Succeed")
    {
        this->username = username;
        this->max_score = GetMaxScoreFromDB();
    }
    else
    {
        throw r.text;
    }
}

// new user
void Client::SignUp()
{
    std::string username;
    std::string password;

    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    std::string signup_url = std::string(BASE_URL) + std::string("signup");
    json json_data;
    json_data["username"] = username;
    json_data["password"] = password;

    cpr::Response r = cpr::Post(cpr::Url{signup_url},
                                cpr::Body{json_data.dump()},
                                cpr::Header{{"Content-Type", "application/json"}});

    if (r.text == "Succeed")
    {
        this->username = username;
        this->max_score = GetMaxScoreFromDB();
    }
    else
    {
        throw r.text;
    }

}

int Client::GetMaxScoreFromDB()
{
    std::string get_game_url = std::string(BASE_URL) + this->username + std::string("/games/1");
    cpr::Response r = cpr::Get(cpr::Url{get_game_url});

    json json_data = json::parse(r.text);
    return json_data["score"];
}