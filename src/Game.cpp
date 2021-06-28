#include "Game.h"
#include <iostream>
#include <iomanip>

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#endif
#ifdef __unix__
    #include <unistd.h>
    #include <termios.h>
	#include <fcntl.h>
#endif

#ifdef __unix__
	int kbhit(void)
	{
		struct termios oldt, newt;
		int ch;
		int oldf;

		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

		ch = getchar();

		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);

		if(ch != EOF)
		{
		ungetc(ch, stdin);
		return 1;
		}

		return 0;
	}

    char getch()
	{
		char c;
		system("stty raw");
		c = getchar();
		system("stty sane");
		return(c);
	}
#endif

void ClearScreen()
{
    #ifdef _WIN32
        system("cls");
    #endif
    #ifdef __unix__
        system("clear");
    #endif
}

Direction Game::TakeInput()
{
    Direction direction = NOP;

#ifdef _WIN32
    if (_kbhit())
    {
        char ch = _getch();
        switch (ch)
        {
        case 'w': // up
            direction = UP;
            break;

        case 's': // down
            direction = DOWN;
            break;

        case 'd': // right
            direction = RIGHT;
            break;

        case 'a': // left
            direction = LEFT;
            break;
        }
    }
#endif

// w a s d olarak değiştir
#ifdef __unix__
    if (kbhit())
    {
        if (getch() == 27) {    // if the first value is esc
            getch();                // skip the [
            switch(getch())         // real value
            {
            case 65:
                direction = UP;
                break;
            case 66:
                direction = DOWN;
                break;
            case 67:
                direction = RIGHT;
                break;
            case 68:
                direction = LEFT;
                break;
            }
        }
    }
#endif

    return direction;
}


Game::Game(Map& _map, Snake& _snake)
    : map(_map), snake(_snake), game_over(false)
{
}

Game::~Game()
{
    map.ClearMap();
    snake.KillSnake();
}

void Game::GameStart()
{
    ClearScreen();
    map.GenerateFood(snake);
    map.UpdateMapAndDraw(snake);
}

void Game::GameLoop()
{
    ClearScreen();

#if !DEBUG
    Direction direction = TakeInput();
#else
    Direction direction = (Direction) (1 + rand() % 4);
#endif

    direction_history.push_back(direction);

    snake.ChangeDirectionAndMove(direction);
    game_over = !(snake.IsAlive());

    if (map.DoSnakeAteFood(snake))
    {
        snake.AddNewBone();
        map.GenerateFood(snake);
    }

    std::cout << std::string(map.GetDimensions().second - 3, ' ') << "SNAKE GAME" << "\n";
    std::cout << "Name:  " << snake.GetName() << "\n" << "Score: " << snake.GetScore() << "\n\n";
    map.UpdateMapAndDraw(snake);
}

void Game::GameEnd()
{
    std::cout << "\n\nYour snake " << snake.GetName() << " is dead!\n";
    std::cout << "Score: " << snake.GetScore() << "\n";

#if DEBUG
    std::cout << "-----------------------------------------------------\n";
    for (auto it = direction_history.begin(); it != direction_history.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n-----------------------------------------------------\n";
#endif
}