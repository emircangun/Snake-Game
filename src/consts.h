#pragma once

#define HEIGHT      15
#define WIDTH       15
#define MAX_WIDTH   100
#define MAX_HEIGHT  100

#define INIT_SNAKE_LEN      3
#define INIT_SNAKE_HEAD_X   2
#define INIT_SNAKE_HEAD_Y   3
#define MAX_SNAKE_NAME_LEN  10
#define MAX_SNAKE_INIT_LEN  5

#define MAP_SNAKE_BODY '#'
#define MAP_SNAKE_HEAD '+'
#define MAP_FOOD       '8'
#define MAP_BLANK      '-'

#define SLEEP_TIME 1000*0.2

enum Direction
{
    NOP, // stay, no operation
    UP,
    RIGHT,
    DOWN,
    LEFT
};
