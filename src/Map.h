#pragma once

#include "Snake.h"
#include <vector>

class Map
{
private:
    std::vector<std::vector<char>> map;
    std::pair<int, int> food;
    int width;
    int height;

public:
    void CreateMap(int = WIDTH, int = HEIGHT);
    void ClearMap();
    void GenerateFood(const Snake&);
    void UpdateMap(const Snake&);
    void DrawMap();
    bool DoSnakeAteFood(const Snake&);

};