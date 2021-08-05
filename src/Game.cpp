#include "Game.h"
#include "consts.h"
#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

#ifndef _WIN32
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

    if (ch != EOF)
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
    return (c);
}
#endif

void ClearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

char UP_KEY = 'w';
char DOWN_KEY = 's';
char RIGHT_KEY = 'd';
char LEFT_KEY = 'a';
char STOP_KEY = 'r';

Game::Game(Map &_map, Snake &_snake, Client &_user)
    : map(_map), snake(_snake), game_over(false), user(_user)
{
}

Game::~Game()
{
    map.ClearMap();
    snake.KillSnake();
}

void Game::StartGame()
{
    ClearScreen();
    map.GenerateFood(snake);
    map.UpdateMapAndDraw(snake);
}

char Game::TakeInput()
{
#ifdef _WIN32
    if (_kbhit())
    {
        char ch = _getch();
        return ch;
    }
#endif

#ifndef _WIN32
    if (kbhit())
    {
        char ch = getch();
        return ch;
    }
#endif

    return 0;
}

bool Game::HandleInput(char input, Direction &direction)
{
    if (input == UP_KEY)
    {
        direction = UP;
        return true;
    }
    else if (input == LEFT_KEY)
    {
        direction = LEFT;
        return true;
    }
    else if (input == DOWN_KEY)
    {
        direction = DOWN;
        return true;
    }
    else if (input == RIGHT_KEY)
    {
        direction = RIGHT;
        return true;
    }
    else
    {
        direction = NOP;
        // stop game
        if (input == STOP_KEY)
        {
            return false;
        }
    }
    return true;
}

// return true if quit is chosen; otherwise return false
bool Game::StopGame(bool exit)
{
    while (!exit)
    {
        int choice;
        // change keys
        // resume
        // quit
        do
        {
            std::cout << "1. Resume\n";
            std::cout << "2. Change keys\n";
            std::cout << "3. Quit game\n";
            std::cout << ">>> ";
            std::cin >> choice;
        } while (choice < 1 || choice > 3);

        if (choice == 1)
        {
            exit = true;
        }
        else if (choice == 2)
        {
            // aynı harften yapamamayı ekle
            int change_key;
            do
            {
                std::cout << "\nChoose the key you want to change.\n";
                std::cout << "1. Up key    : " << UP_KEY << "\n";
                std::cout << "2. Down key  : " << DOWN_KEY << "\n";
                std::cout << "3. Right key : " << RIGHT_KEY << "\n";
                std::cout << "4. Left key  : " << LEFT_KEY << "\n";
                std::cout << "5. Return menu\n";
                std::cout << ">>> ";
                std::cin >> change_key;
            } while (change_key < 1 || change_key > 5);

            if (change_key == 5)
                return false;

            char new_key;
            std::cout << "New key: ";
            std::cin >> new_key;
            if (change_key == 1)
                UP_KEY = new_key;
            else if (change_key == 2)
                DOWN_KEY = new_key;
            else if (change_key == 3)
                RIGHT_KEY = new_key;
            else if (change_key == 4)
                LEFT_KEY = new_key;
        }
        else if (choice == 3)
        {
            return true;
        }
    }
    return false;
}

// return true to terminate program
bool Game::GameLoop()
{
    ClearScreen();

    char input = TakeInput();
    Direction direction;
    // true if input is a direction
    bool is_input_stop = HandleInput(input, direction);

    bool quit = false;
    if (!is_input_stop)
        quit = StopGame(is_input_stop);

    if (quit)
        return true;

    // go on play
    direction_history.push_back(direction);

    snake.ChangeDirectionAndMove(direction);
    game_over = !(snake.IsAlive());

    if (map.DoSnakeAteFood(snake))
    {
        snake.AddNewBone();
        map.GenerateFood(snake);

        // increase game speed
        if (Speed < MAX_SPEED_CONST)
        {
            int _score = snake.GetScore();
            double tmp = Speed;
            if (_score >= 10 && _score < 40 && _score % 10 == 0) // 10 20 30
                tmp += 3 + _score / 10;                          // 1 2 3
            else if (_score >= 40 && _score % 10 == 0)           // 40 50 60 ...
                tmp += 8;

            if (tmp < MAX_SPEED_CONST)
                Speed = tmp;
            else
                Speed = MAX_SPEED_CONST;
        }
    }

    std::cout << std::string(Width - 3, ' ') << "SNAKE GAME"
              << "\n\n";
    std::cout << "Up Key    : " << UP_KEY << "\n";
    std::cout << "Down Key  : " << DOWN_KEY << "\n";
    std::cout << "Right Key : " << RIGHT_KEY << "\n";
    std::cout << "Left Key  : " << LEFT_KEY << "\n";
    std::cout << "Pause Key : " << STOP_KEY << "\n\n";

    std::cout << "Name: " << user.GetUsername() << "\nMaximum Score: " << user.GetMaxScore() << "\n\n";

    std::cout << "Current Score: " << snake.GetScore() << "\nSpeed: " << Speed << "\n";
    std::cout << "\n(Press " << STOP_KEY << " to stop game.)\n";

    map.UpdateMapAndDraw(snake);
    return false;
}

void Game::EndGame()
{
    std::cout << "\nYour snake " << user.GetUsername() << " is dead!\n";
    std::cout << "Score: " << snake.GetScore() << "\n\n";

    std::cout << "--- Verify yourself to keep this score ---\n";
    std::string password;
    bool isPasswordCorrect = true;
    do
    {
        std::cout << "Password: ";
        std::cin >> password;
        isPasswordCorrect = user.AddGame(password, this->direction_history, snake.GetScore());
    } while (!isPasswordCorrect);

#if DEBUG
    std::cout << "-----------------------------------------------------\n";
    for (auto it = direction_history.begin(); it != direction_history.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n-----------------------------------------------------\n";
#endif
}