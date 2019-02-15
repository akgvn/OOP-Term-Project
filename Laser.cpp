// akgvn - 2019/01
// CENG241 Term Project

#include "Laser.h"
#include "GoManager.h"
#include "rlutil.h"

using namespace std;
using namespace rlutil;

Laser::Laser() : GameObject()
{
    sprite = "-";
    visible = false;
    direction = 1;
}

void Laser::draw()
{
    // Draw the laser to screen
    if (visible)
    {
        locate(getPX(), getPY());
        cout << " ";

        // Change the color
        if (this->direction == -1)
        {
            // Enemy laser
            setColor(YELLOW);
        }
        else
        {
            // Player laser
            setColor(LIGHTCYAN);
        }

        locate(this->getX(), this->getY());
        cout << this->sprite;

        setColor(GREY);
    }
}

void Laser::update()
{
    if (visible)
    {
        // update the location
        this->setX(getX() + (direction));
        this->setY(getY());
    }

    if (getX() >= 80 || getX() <= 1)
    {
        // out of screen bounds
        destroy();
    }
}

void Laser::destroy()
{
    visible = false;

    // Clear the after image.
    locate(getPX(), getPY());
    cout << " ";
    locate(getX(), getY());
    cout << " ";

    // Inform the manager.
    GoManager::activeLsr--;
}