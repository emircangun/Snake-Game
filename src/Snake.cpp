#include "Snake.h"

void Snake::InitSnake()
{
    for (int i = 0; i < INIT_SNAKE_LEN; ++i)
    {
        std::pair<int, int> bone = std::make_pair(INIT_SNAKE_HEAD_X, INIT_SNAKE_HEAD_Y - i);
        body.push_back(bone);
    }

    head = body[0];
    last_tail = std::make_pair(INIT_SNAKE_HEAD_X, INIT_SNAKE_HEAD_Y - INIT_SNAKE_LEN);
    isAlive = true;
    score = 0;
    go = NOP;
}

void Snake::KillSnake()
{
    body.clear();
    isAlive = false;
}

void Snake::Move()
{
    if (go != NOP)
    {
        last_tail = body.back();
        int next_x, next_y, cur_x, cur_y;
        for (int i = body.size() - 1; i > 0; --i)
        {
            next_x = body[i - 1].first;
            next_y = body[i - 1].second;
            cur_x = body[i].first;
            cur_y = body[i].second;

            if (next_x == cur_x - 1) // up
                body[i].first--;
            else if (next_x == cur_x + 1) // down
                body[i].first++;
            else if (next_y == cur_y - 1) // left
                body[i].second--;
            else if (next_y == cur_y + 1) // right
                body[i].second++;
        }

        switch(go)
        {
            case UP:
            {
                if (head.first == 0)
                {
                    // change map to up if there is, if there is not snake is dead
                    isAlive = false;
                    return;
                }
                body[0].first--;
                break;
            }
            case DOWN:
            {
                if (head.first == (int)Height - 1)
                {
                    // change map to down if there is, if there is not snake is dead
                    isAlive = false;
                    return;
                }
                body[0].first++;
                break;
            }
            case RIGHT:
            {
                if (head.second == (int)Width - 1)
                {
                    // change map to right if there is, if there is not snake is dead
                    isAlive = false;
                    return;
                }
                body[0].second++;
                break;
            }
            case LEFT:
            {
                if (head.second == 0)
                {
                    // change map to left if there is, if there is not snake is dead
                    isAlive = false;
                    return;
                }
                body[0].second--;
                break;
            }
            case NOP:
                break;
        }

        head = body[0];
        
        if (CheckCollisionInside())
            isAlive = false;
    }
}

void Snake::ChangeDirectionAndMove(Direction new_direction)
{
    if (new_direction == NOP)
        new_direction = go;

    if (!((go == DOWN  && new_direction == UP)    ||
          (go == UP    && new_direction == DOWN)  ||
          (go == LEFT  && new_direction == RIGHT) ||
          (go == RIGHT && new_direction == LEFT)))
    {
        go = new_direction;
    }

    Move();
}

void Snake::AddNewBone()
{
    score++;
    
    std::pair<int, int> bone = last_tail;
    body.push_back(bone);
}

bool Snake::CheckFoodCollision(int x, int y) const
{
    std::pair<int, int> target = std::make_pair(x, y);
    for (int i = 0; i < (int) body.size(); ++i)
        if (target == body[i])
            return true;

    return false;
}

bool Snake::CheckCollisionInside() const
{
    for (int i = 1; i < (int) body.size(); ++i)
        if (head == body[i])
            return true;
    
    return false;
}