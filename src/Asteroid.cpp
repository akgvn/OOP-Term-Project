// akgvn - 2019/01
// CENG241 Term Project

#include "Asteroid.h"

#include "rlutil.h"
#include "GoManager.h"

using namespace std;
using namespace rlutil;

Asteroid::Asteroid()
{
    sprite = "0";
    health = 1;
}

Asteroid::Asteroid(int nx, int ny)
{
    sprite = "0";
    health = 1;
    setX(nx);
    setY(ny);
}

void Asteroid::update()
{
    // Updates the state of this asteroid.
    if (health > 0)
    {
        if (getX() == 1)
        {
            destroy();
        }
        setX(getX() - 1);
        setY(getY());
    }
}
void Asteroid::draw()
{
    // Draws the asteroid to screen if health > 0
    if (health)
    {
        // Asteroids are red.
        setColor(RED);

        // Delete the after image.
        locate(getPX(), getPY());
        cout << " ";

        // Draw the current location.
        locate(getX(), getY());
        cout << sprite;

        // Reset the color.
        setColor(GREY);
    }
}

void Asteroid::destroy()
{
    // Destroy the asteroid.
    health = 0;
    visible = false;

    // Delete the after image after destroying.
    locate(getPX(), getPY());
    cout << " ";
    locate(getX(), getY());
    cout << " ";

    // Inform the manager.
    GoManager::activeAst--;

    GoManager::points += 1;
}