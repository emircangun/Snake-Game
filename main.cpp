#include "./src/Game.h"
#include "./src/Snake.h"
#include "./src/Map.h"
#include "./src/consts.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

//
void GameSleep(int sleepMs)
{
    #ifdef _WIN32
        Sleep(sleepMs);
    #else
        usleep(sleepMs * 1000);
    #endif
}

//

#define HELP_COUT {               \
                    std::cout << "\nExample run - (width, height, speeed):  ./main 20 20 1.5\n"; \
                    std::cout << "Example run - initial values:             ./main\n\n"; \
                    std::cout << "-W : Width , max " << MAX_WIDTH << ", min " << MIN_WIDTH << ", init " << INIT_WIDTH << "\n"; \
                    std::cout << "-H : Height, max " << MAX_HEIGHT << ", min " << MIN_HEIGHT << ", init " << INIT_HEIGHT << "\n"; \
                    std::cout << "-S : Speed , max " << MAX_SPEED_CONST << ", min " << MIN_SPEED_CONST  << ", init " << INIT_SPEED_CONST << "\n\n"; \
                  }

void CommandLineHandling(int argc, char* argv[])
{
    if (argc == 1)
    {
        Width  = INIT_WIDTH;
        Height = INIT_HEIGHT;
        Speed  = INIT_SPEED_CONST;
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-help") == 0)
            throw "Help";
    }
    else if (argc == 4)
    {
        std::stringstream ss;
        {
            int tmp_width;
            ss << argv[1];  
            ss >> tmp_width;
            ss.clear();
            if (tmp_width < MIN_WIDTH || tmp_width > MAX_WIDTH)
                throw "Please, select from the appropriate range.";
            else
                Width = tmp_width;
        }
        {
            int tmp_height;
            ss << argv[2];  
            ss >> tmp_height;
            ss.clear();
            if (tmp_height < MIN_HEIGHT || tmp_height > MAX_HEIGHT)
                throw "Please, select from the appropriate range.";
            else
                Height = tmp_height;
        }
        {
            double tmp_speed;
            ss << argv[3];  
            ss >> tmp_speed;
            ss.clear();
            if (tmp_speed < MIN_SPEED_CONST|| tmp_speed > MAX_SPEED_CONST)
                throw "Please, select from the appropriate range.";
            else
                Speed = tmp_speed;
        }
    }
    else
    {
        throw "Please, use command below.";
    }
}

void GameOn()
{
    std::string name;
    std::cout << "Name for your snake: ";
    std::cin >> name;

    Snake snake;
    try {
        snake.InitSnake(name);
    } catch (const char* err) {
        std::cout << err << "\n";
    }

    Map map;
    map.CreateMap(Width, Height);

    Game game(map, snake);
    game.GameStart();

    while (!game.IsGameEnd())
    {
        game.GameLoop();
        GameSleep(1000.0 / Speed);
    }

    game.GameEnd();
}

/////////////////////////// TO DO /////////////////////////////

// durdurma özelliği
// hız arttırma özelliği

int main(int argc, char* argv[])
{
    try {
        CommandLineHandling(argc, argv);
    } catch (const char* error) {
        std::cout << error;
        HELP_COUT
        return 1;
    }

    srand(time(NULL));
    GameOn();

    getchar();

    return 0;
}