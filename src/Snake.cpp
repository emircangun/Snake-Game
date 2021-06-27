#include "Snake.h"

void Snake::InitSnake(std::string name, unsigned int init_len)
{
    if (name.length() >= MAX_SNAKE_NAME_LEN)
        throw std::string("Name is too long!");

    if (init_len >= MAX_SNAKE_INIT_LEN)
        throw std::string("Length is too much!");

    if (init_len <= 0)
        throw std::string("Choose a positive len!");

    this->name = name;
    for (int i = 0; i < init_len; ++i)
    {
        std::pair<int, int> bone = std::make_pair(INIT_SNAKE_HEAD_X, INIT_SNAKE_HEAD_Y - i);
        body.push_back(bone);
    }

    head = body[0];
    isAlive = true;
    score = 0;
    last_direction = NOP;
    go = NOP;
}

void Snake::KillSnake()
{
    body.clear();
    isAlive = false;
}

void Snake::Move()
{
    int next_x, next_y, cur_x, cur_y;
    for (int i = body.size() - 1; i > 0; ++i)
    {
        next_x = body[i - 1].first;
        next_y = body[i - 1].second;
        cur_x = body[i].first;
        cur_y = body[i].second;

        if (next_x == cur_x - 1) // up
            body[i].first--;
        else if (next_x == cur_x + 1) // down
            body[i].first++;
        else if (next_y == cur_x - 1) // left
            body[i].second--;
        else if (next_y == cur_x + 1) // right
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
            head.first--;
            break;
        }
        case DOWN:
        {
            if (head.first == HEIGHT - 1)
            {
                // change map to down if there is, if there is not snake is dead
                isAlive = false;
                return;
            }
            head.first++;
            break;
        }
        case RIGHT:
        {
            if (head.second == WIDTH - 1)
            {
                // change map to right if there is, if there is not snake is dead
                isAlive = false;
                return;
            }
            head.second++;
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
            head.second--;
            break;
        }
    }

    if (CheckCollisionInside())
    {
        isAlive = false;
    }
}

void Snake::ChangeDirection(Direction new_direction)
{
    if (!((go == DOWN  && new_direction == UP)    ||
          (go == UP    && new_direction == DOWN)  ||
          (go == LEFT  && new_direction == RIGHT) ||
          (go == RIGHT && new_direction == LEFT)))
    {
        last_direction = go;
        go = new_direction;
    }

    Move();
}

bool Snake::CheckEatFood(int x, int y) const
{
    std::pair<int, int> target = std::make_pair(x, y);
    for (int i = 0; i < body.size(); ++i)
        if (target == body[i])
            return true;

    return false;
}

bool Snake::CheckCollisionInside()
{
    for (int i = 0; i < body.size(); ++i)
    {
        if (head == body[i])
        {
            isAlive = false;
            return true;
        }
    }
    
    return false;
}