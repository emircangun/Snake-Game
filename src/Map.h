#pragma once

#include "Snake.h"

class Map
{
private:
    std::vector<std::vector<char>> map;
    std::pair<int, int> food;
    int width;
    int height;

public:
    void CreateMap(int = INIT_WIDTH, int = INIT_HEIGHT);
    void ClearMap();
    void GenerateFood(const Snake&);
    void UpdateMapAndDraw(const Snake&);
    bool DoSnakeAteFood(const Snake&);
};