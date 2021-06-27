#pragma once

#include "consts.h"
#include <string>
#include <vector>

class Snake
{
private:
    std::string name;
    unsigned int score; // counter of foods the snake ate
    std::vector<std::pair<int, int>> body; // body of snake with coordinates <x,y> body[0] is head
    std::pair<int, int> head;
    bool isAlive; // true if the snake is alive

    
public:
    void InitSnake(std::string, unsigned int = INIT_SNAKE_LEN);
    void KillSnake();
    void Move(Direction);
    bool CheckCollision(int, int);

    bool IsAlive()        const { return isAlive; }
    std::string GetName() const { return name; }
    int GetScore()        const { return score;  }
    int GetLength()       const { return body.size(); }
    std::vector<std::pair<int, int>> GetBody() const { return body; }
};