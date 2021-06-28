#pragma once

#define DEBUG 0

#define INIT_HEIGHT 10
#define INIT_WIDTH  10
#define MAX_HEIGHT  50
#define MAX_WIDTH   50
#define MIN_HEIGHT  8
#define MIN_WIDTH   8

#define INIT_SPEED_CONST 5
#define MAX_SPEED_CONST  10 
#define MIN_SPEED_CONST  0.5 

#define INIT_SNAKE_LEN      3
#define INIT_SNAKE_HEAD_X   2
#define INIT_SNAKE_HEAD_Y   3
#define MAX_SNAKE_NAME_LEN  10
#define MAX_SNAKE_INIT_LEN  3

#define MAP_SNAKE_BODY '#'
#define MAP_SNAKE_HEAD '+'
#define MAP_FOOD       '8'
#define MAP_BLANK      '-'


enum Direction
{
    NOP, // stay, no operation
    UP,
    RIGHT,
    DOWN,
    LEFT
};
