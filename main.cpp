#include "./src/StartGame.h"

unsigned int Width;
unsigned int Height;
double Speed;

int main(int argc, char* argv[])
{
    try {
        SnakeGame::CommandLineHandling(argc, argv);
    } catch (const char* error) {
        std::cout << error;
        HELP_COUT
        return 1;
    }

    srand(time(NULL));
    
    SnakeGame::GameOn();

    getchar();

    return 0;
}