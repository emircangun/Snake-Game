#include "./src/Game.h"
#include "./src/Snake.h"
#include "./src/Map.h"

#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#endif
#ifdef __unix__
    #include <unistd.h>
#endif

using namespace std;

void GameSleep(int sleepMs)
{
    #ifdef _WIN32
        Sleep(sleepMs);
    #endif
    #ifdef __unix__
        usleep(sleepMs * 1000);
    #endif
}

int main()
{
    string name;
    cout << "Name for your snake: ";
    cin >> name;

    Snake snake;
    snake.InitSnake(name);
    Map map;
    map.CreateMap();

    Game game(map, snake);
    game.GameStart();
    while (!game.IsGameEnd())
    {
        game.GameLoop();
        GameSleep(SLEEP_TIME);
    }

    game.GameEnd();

    return 0;
}