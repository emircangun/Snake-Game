#pragma once

#include "Game.h"
#include "Snake.h"
#include "Map.h"
#include "consts.h"
#include "../client/Client.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define HELP_COUT {               \
                    std::cout << "\nExample run - (width, height, speeed):  ./main 20 20 1.5\n"; \
                    std::cout << "Example run - initial values:             ./main\n\n"; \
                    std::cout << "-W : Width , max " << MAX_WIDTH << ", min " << MIN_WIDTH << ", init " << INIT_WIDTH << "\n"; \
                    std::cout << "-H : Height, max " << MAX_HEIGHT << ", min " << MIN_HEIGHT << ", init " << INIT_HEIGHT << "\n"; \
                    std::cout << "-S : Speed , max " << MAX_SPEED_CONST << ", min " << MIN_SPEED_CONST  << ", init " << INIT_SPEED_CONST << "\n\n"; \
                  }

namespace SnakeGame
{
    bool IsServerOnline();
    void GameSleep(int sleepMs);
    void CommandLineHandling(int argc, char* argv[]);
    void StartMenu(Client &user);
    void GameOn();
}