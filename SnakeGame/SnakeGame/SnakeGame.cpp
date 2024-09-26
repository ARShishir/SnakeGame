//Snake Game

//Abdur Rahaman Shishir
#include<iostream>
#include <conio.h>
#include <cstdlib> // For rand() function
#include <windows.h> // For Sleep()

using namespace std;

bool gameover;

const int width = 20;
const int height = 17;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; // Snake tail coordinates
int nTail;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // Controls
eDirecton dir;

void Setup()
{
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width; // Display fruit in a random place
    fruitY = rand() % height;
    score = 0;
}

void Draw()
{
    system("cls"); // Use "cls" for Windows. Use "clear" if on Linux.

    // Draw the top boundary
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    // Draw the game area
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) // Left wall
                cout << "|";

            if (i == y && j == x) // Snake head
                cout << "*";
            else if (i == fruitY && j == fruitX) // Fruit
                cout << "O";
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i) // Snake tail
                    {
                        cout << "*";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1) // Right wall
                cout << "|";
        }
        cout << endl;
    }

    // Draw the bottom boundary
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    // Display score
    cout << "Score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void Logic()
{
    // Update tail positions
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move snake based on direction
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // Snake wrapping logic
    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    // Check for self-collision
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;
    }

    // Snake eats the fruit
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    Setup();

    while (!gameover)
    {
        Draw();
        Input();
        Logic();
        Sleep(100); // Slow down the game loop
    }

    return 0;
}
