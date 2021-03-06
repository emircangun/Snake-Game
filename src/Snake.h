#pragma once

#include "consts.h"
#include <string>
#include <vector>

class Snake
{
private:
    unsigned int score; // counter of foods the snake ate
    std::vector<std::pair<int, int>> body; // body of snake with coordinates <x,y> body[0] is head
    std::pair<int, int> head;
    std::pair<int, int> last_tail;
    Direction go;
    bool isAlive; // true if the snake is alive
    
public:
    void InitSnake(); // initializes snake
    void KillSnake(); // killing snake, delete contents of body
    void Move();
    void ChangeDirectionAndMove(Direction);
    void AddNewBone();
    bool CheckFoodCollision(int, int) const;
    bool CheckCollisionInside() const;

    // getter functions
    bool IsAlive()                             const { return isAlive; }
    int GetScore()                             const { return score;  }
    int GetLength()                            const { return body.size(); }
    std::pair<int, int> GetHead()              const { return head; }
    std::vector<std::pair<int, int>> GetBody() const { return body; }
    Direction GetCurrentDirection()            const { return go; }
};