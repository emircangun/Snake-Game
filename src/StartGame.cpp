#include "StartGame.h"

void SnakeGame::GameSleep(int sleepMs)
{
#ifdef _WIN32
    Sleep(sleepMs);
#else
    usleep(sleepMs * 1000);
#endif
}

void SnakeGame::CommandLineHandling(int argc, char *argv[])
{
    if (argc == 1)
    {
        Width = INIT_WIDTH;
        Height = INIT_HEIGHT;
        Speed = INIT_SPEED_CONST;
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
            if (tmp_speed < MIN_SPEED_CONST || tmp_speed > MAX_SPEED_CONST)
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

// printing the start menu - login or signup
void SnakeGame::StartMenu(Client &user)
{
    int choice;
    do
    {
        std::cout << "1. Login\n2. SignUp\n>>> ";
        std::cin >> choice;
    } while (choice < 1 || choice > 2);

    bool response;
    if (choice == 1)
    {
        do
        {
            response = user.Login();
        } while (!response);
    }
    else if (choice == 2)
    {
        do
        {
            response = user.SignUp();
        } while (!response);
    }
}

// starting the game
void SnakeGame::GameOn()
{
    Client user = Client();

    SnakeGame::StartMenu(user);

    Snake snake;
    snake.InitSnake();
    Map map;
    map.CreateMap(Width, Height);

    Game game(map, snake, user);
    game.StartGame();

    bool quit = false;
    while (!game.IsGameEnd() && !quit)
    {
        quit = game.GameLoop();
        GameSleep(1000.0 / Speed);
    }

    if (game.IsGameEnd())
        game.EndGame();

    if (quit)
        std::cout << "Program terminated!\n";
}