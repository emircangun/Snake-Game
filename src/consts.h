#pragma once

#define WIDTH 50
#define HEIGHT 50
#define MAX_WIDTH 100
#define MAX_HEIGHT 100

#define INIT_SNAKE_LEN 3
#define INIT_SNAKE_HEAD_X WIDTH/2
#define INIT_SNAKE_HEAD_Y HEIGHT/2
#define MAX_SNAKE_NAME_LEN 10
#define MAX_SNAKE_INIT_LEN 5

#define MAP_SNAKE_BODY '#'
#define MAP_SNAKE_HEAD '+'
#define MAP_FOOD       '8'
#define MAP_BLANK      '-'

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NOP // stay, no operation
};
