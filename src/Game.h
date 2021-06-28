#pragma once

#include "Snake.h"
#include "Map.h"

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
    void StartGame();
    bool StopGame(bool);
    void EndGame();
    bool GameLoop();
    char TakeInput();
    bool HandleInput(char, Direction&);
    bool IsGameEnd() const { return game_over; }
};