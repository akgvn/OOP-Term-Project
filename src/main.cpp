// akgvn - 2019/01
// CENG241 Term Project

#include <iostream> // to use cout...
#include <chrono>   // to time the frames correctly.
#include <string>
#include <cstdlib> // for usage of random number generator
#include <ctime>   // for random nuber generator

#include "GameObject.h"
#include "Player.h"
#include "Laser.h"
#include "Asteroid.h"
#include "GoManager.h"

#include "rlutil.h"

using namespace std;
using namespace std::chrono;
using namespace rlutil;

void drawBounds()
{
    // Drawing screen boundaries

    int i;
    setBackgroundColor(GREY);
    for (i = 1; i < 27; i++)
    {
        locate(81, i);
        cout << "|";
    }
    for (i = 1; i < 81; i++)
    {
        locate(i, 26);
        cout << "-";
    }
    setBackgroundColor(BLACK);
}

int main()
{
    srand(time(NULL));
    hidecursor();
    int frame = 0, i;

    drawBounds();

    setColor(YELLOW);
    gotoxy(20, 10);
    cout << "Space Shoot 'em Up by Abdulkerim Guven";
    gotoxy(20, 11);
    cout << "CENG241 TERM PROJECT";

    setColor(GREY);
    gotoxy(20, 15);
    anykey("Press any key start the game...");

    cls();
    drawBounds();

    GoManager::points = 0;

    time_point<system_clock> timer = system_clock::now(); // to count Frames

    while (GoManager::inGame)
    {
        timer += milliseconds(100); // Draw the screen every 100 ms

        GoManager::updateState(frame); // Update the game state

        while (system_clock::now() < timer)
        {
            continue;
        } // Wait until the time for next frame.

        hidecursor();
        GoManager::drawEverything(); // Draw every game object.

        frame++;
    }

    setColor(RED);
    gotoxy(85, 20);
    anykey("Press any key to quit...");
    return 0;
}