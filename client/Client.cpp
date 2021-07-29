#include "Client.h"
#include "connections.h"
#include <iostream>
#include <string>
#include <cpr/cpr.h>

Client::Client()
{
}

Client::~Client()
{
}

void Client::Login()
{
    std::string username;
    std::string password;

    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    std::string login_url = std::string(BASE_URL) + std::string("login");
    std::string json_data = "{\"username\":\"" + username + "\",\"password\":\"" + password + "\"}";
    cpr::Response r = cpr::Post(cpr::Url{login_url},
                                cpr::Body{json_data},
                                cpr::Header{{"Content-Type", "application/json"}});

    std::cout << login_url << std::endl;
    std::cout << json_data << std::endl;
    std::cout << r.text << std::endl;

    if (r.text == "Succeed")
    {
    
    }
    else
    {
        throw "Credentials are wrong!";
    }
}

void Client::SignUp()
{
    std::string username;
    std::string password;

    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    std::string signup_url = std::string(BASE_URL) + std::string("signup");
    cpr::Response r = cpr::Post(cpr::Url{signup_url},
                                cpr::Body{"asdf"});

    std::cout << r.text << std::endl;
}