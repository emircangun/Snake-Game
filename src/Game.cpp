#include "Game.h"
#include <iostream>

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
    Direction direction;

#ifdef _WIN32
    if (_kbhit())
    {
        char ch = _getch();
        if (ch == 0 || ch == 224)
        {
            ch = _getch();
            switch (ch)
            {
            case 72: // up
                direction = UP;
                break;

            case 80: // down
                direction = DOWN;
                break;

            case 77: // right
                direction = RIGHT;
                break;

            case 75: // left
                direction = LEFT;
                break;
            }
        }
    }
#endif

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
}

#define DEBUG 1

void Game::GameLoop()
{
    ClearScreen();

    if (map.DoSnakeAteFood(snake))
        map.GenerateFood(snake);
    
    map.UpdateMap(snake);
    map.DrawMap();
    
    Direction direction = TakeInput();
#if DEBUG
    std::cout << "\n\n" << direction << "\n\n";
#endif
    snake.ChangeDirection(direction);
    game_over = !(snake.IsAlive());
}