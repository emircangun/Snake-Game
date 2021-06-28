#pragma once

#include "Snake.h"
#include "Map.h"
#include "consts.h"

class Game
{
private:
    Map& map;
    Snake& snake;
    bool game_over;
    std::vector<Direction> direction_history;

public:
    Game(Map&, Snake&);
    ~Game();
    void GameStart();
    void GameEnd();
    void GameLoop();
    Direction TakeInput();
    bool IsGameEnd() const { return game_over; }
};