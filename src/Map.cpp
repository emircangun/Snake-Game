#include "Map.h"
#include <iostream>

void Map::CreateMap(int Width, int Height)
{
    if (Width <= 0        || Height <= 0 ||
        Width > MAX_WIDTH || Height > MAX_HEIGHT)
    {
        throw std::string("Please, choose appropriate dimensions!");
    }

    width = Width;
    height = Height;
    map.resize(height, std::vector<char>(Width, MAP_BLANK));
}


void Map::ClearMap()
{
    for (int i = 0; i < height; ++i)
        map[i].clear();
    map.clear();
}

void Map::GenerateFood(const Snake& snake)
{
    // random sayıları daha iyi üret
    // kontrol aşaması zaman alabiliyor
    int x, y;
    do {
        x = rand() % height;
        y = rand() % width;
    } while (snake.CheckFoodCollision(x, y));

    food = std::make_pair(x, y);
}

void Map::UpdateMapAndDraw(const Snake& snake)
{
    // updating content of map
    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            map[i][j] = MAP_BLANK;

    auto snake_body = snake.GetBody();
    map[snake_body[0].first][snake_body[0].second] = MAP_SNAKE_HEAD;
    for (int i = 1; i < snake.GetLength(); ++i)
        map[snake_body[i].first][snake_body[i].second] = MAP_SNAKE_BODY;

    map[food.first][food.second] = MAP_FOOD;


    // drawing map
    for (int i = 0; i < width + 2; ++i)
    {
        std::cout << "& ";
    }
    std::cout << "\n";

    for (int i = 0; i < height; ++i)
    {
        std::cout << "& ";
        for (int j = 0; j < width; ++j)
        {
            std::cout << map[i][j] << " ";
        }
        std::cout << "&";

    #ifdef _WIN32
        std::cout << "\r\n";
    #else
        std::cout << "\n";
    #endif
    }

    for (int i = 0; i < width + 2; ++i)
    {
        std::cout << "& ";
    }
    std::cout << "\n";
}

bool Map::DoSnakeAteFood(const Snake& snake)
{
    return (snake.GetHead() == food);
}