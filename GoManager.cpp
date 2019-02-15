// akgvn - 2019/01
// CENG241 Term Project

#include "GoManager.h"
#include "rlutil.h"
#include <iostream>
#include <cstdlib>

int GoManager::activeAst = 0;
int GoManager::activeLsr = 0;
int GoManager::activeEny = 0;
int GoManager::maxAst = 15;
int GoManager::maxLsr = 30;
int GoManager::maxEny = 5;
int GoManager::maxObj = 15;
int GoManager::points = 0;
bool GoManager::inGame = true;
Asteroid *GoManager::ast = new Asteroid[GoManager::maxAst];
Laser *GoManager::lsr = new Laser[GoManager::maxLsr];
Enemy *GoManager::eny = new Enemy[GoManager::maxEny];
Player GoManager::p;

void GoManager::spawnLaser(int nx, int ny, int d)
{
    /*
    * There is a limited number of lasers that can be shown
    * on the screen at a time for the to be fast enough.
    * If that limit is not exceeded, we can spawn more lasers.
    */
    int i;
    if (activeLsr < maxLsr)
    {
        for (i = 0; i < maxLsr; i++)
        {
            /*
            * If a laser object in the array is spawned and later destroyed, 
            * it is marked not visible. We can use that object once again.
            */
            if (!(lsr[i].visible))
            {
                lsr[i].visible = true;

                lsr[i].setX(nx);
                lsr[i].setY(ny);

                lsr[i].direction = d;
                activeLsr++;
                return;
            }
        }
    }
}

void GoManager::spawnAsteroid(int nx, int ny)
{
    int i;

    if (activeAst < maxAst)
    {
        for (i = 0; i < maxAst; i++)
        {
            /*
            * If an asteroid object in the array is spawned and later destroyed, 
            * it is marked not visible. We can use that object once again.
            */
            if (!(ast[i].visible))
            {
                ast[i].visible = true;
                ast[i].health = 1;

                ast[i].setX(nx);
                ast[i].setY(ny);

                activeAst++;
                return;
            }
        }
    }
}

void GoManager::spawnEnemy(int nx, int ny)
{
    int i;

    if (activeEny < maxEny)
    {
        for (i = 0; i < maxEny; i++)
        {
            /*
            * If an enemy object in the array is spawned and later destroyed, 
            * it is marked not visible. We can use that object once again.
            */
            if (!(eny[i].visible))
            {
                eny[i].visible = true;
                eny[i].health = 2;

                eny[i].setX(nx);
                eny[i].setY(ny);

                activeEny++;
                return;
            }
        }
    }
}

void GoManager::astController(int frame)
{
    int loc, radius, y, x, i;

    // Calculating where to spawn an asteroid using a random number generator.

    radius = abs(80 - p.getY()) < abs(p.getY() - 80) ? abs(80 - p.getY()) : abs(p.getY() - 80);
    radius /= 2;

    loc = rand() % radius;
    loc /= 2;

    radius = rand() % 7;
    radius /= 2;

    if (frame % 2 == 0)
    {
        y = p.getX() + loc;
        x = 73 - radius;
    }
    else
    {
        y = p.getX() - loc;
        x = 73 + radius;
    }

    if (y < 1 || y > 24)
    {
        // If rn generator doesn't stick to the boundaries we don't listen to it.
        y = 13;
    }
    for (i = 0; i < maxAst; i++)
    {
        if (ast[i].visible)
        {
            if (ast[i].getX() == x && ast[i].getY() == y)
            {
                /*
                * If there is another asteroid object in the coordinates 
                * we were planning to spawn, we change the coordinates.
                */
                x++;
                y++;
            }
        }
    }

    spawnAsteroid(x, y);
}

void GoManager::enyController()
{
    int loc, radius, y, x, i;

    x = 70;
    y = rand() % 15 + 5; // y will be between 5 & 20

    if (y < 1 || y > 24) // If rn generator doesn't stick to boundaries we don't listen to it.
        y = 13;

    for (i = 0; i < maxAst; i++)
    {
        // Don't spawn in taken coordinates.

        if (ast[i].visible)
        {
            if (abs(ast[i].getX() - x) <= 2 && ast[i].getY() == y)
            {
                x++;
                y++;
            }
        }
        if (lsr[i].visible && i < maxLsr)
        {
            if (abs(lsr[i].getX() - x) <= 2 && lsr[i].getY() == y)
            {
                x++;
                y++;
            }
        }
        if (eny[i].visible && i < maxEny)
        {
            if (abs(eny[i].getX() - x) <= 2 && eny[i].getY() == y)
            {
                x++;
                y++;
            }
        }
    }

    spawnEnemy(x, y);
}

void GoManager::updateState(int frame)
{
    int i;

    maxObj = maxAst > maxEny ? maxAst : maxEny;
    maxObj = maxLsr > maxObj ? maxLsr : maxObj;

    p.update();

    if (activeAst < ((maxAst / 3) + 1) || (frame % 15 == 0 && activeAst < maxAst))
    {
        // Spawn asteroids once in a while.
        astController(frame);
    }
    if (activeEny < ((maxEny / 2) + 1) || (frame % 30 == 0 && activeEny < maxEny))
    {
        // Spawn enemies once in a while.
        enyController();
    }

    if (activeAst > 0 || activeLsr > 0 || activeEny > 0)
    {
        // If there is any object on the screen, start updating
        // states and check for collisions with player ship.
        for (i = 0; i < maxObj; i++)
        {
            if (lsr[i].visible && i < maxLsr)
            {
                lsr[i].update();
                collision(p, lsr[i]);
            }
            if (ast[i].visible && i < maxAst)
            {
                if (frame % 4 == 0) // Move every 4 frames.
                    ast[i].update();
                collision(p, ast[i]);
            }
            if (i < maxEny && eny[i].visible)
            {
                if (frame % 3 == 0) // Move very 3 frames.
                    eny[i].update(frame);
                collision(p, eny[i]);
            }
        }

        for (i = 0; i < maxObj; i++)
        {
            if (activeAst > 0 && activeLsr > 0)
            {
                // Checking collisions between lasers and asteroids.
                if (lsr[i].visible && i < maxLsr)
                {
                    for (int j = 0; j < maxLsr; j++)
                    {
                        if (ast[j].visible && j < maxAst)
                        {
                            if (collision(lsr[i], ast[j]))
                                break;
                        }
                    }
                }
                // Checking collisions between lasers and enemies.
                if (lsr[i].visible && i < maxLsr)
                {
                    for (int j = 0; j < 15; j++)
                    {
                        if (eny[j].visible && j < maxAst)
                        {
                            if (collision(lsr[i], eny[j]))
                                break;
                        }
                    }
                }
                // Checking collisions between enemy & players lasers.
                if (lsr[i].visible && i < maxLsr)
                {
                    for (int j = i + 1; j < maxLsr; j++)
                    {
                        if (lsr[j].visible && (i != j) && lsr[i].direction != lsr[j].direction)
                        {
                            if (collision(lsr[i], lsr[j]))
                                break;
                        }
                    }
                }
            }
            else
                break;
        }
    }
}

void GoManager::drawEverything()
{
    int i;

    p.draw();

    // Draw health information.
    rlutil::setColor(rlutil::RED);
    gotoxy(85, 4);
    std::cout << "Health: ";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << p.health;

    // Draw score information.
    rlutil::setColor(rlutil::RED);
    gotoxy(85, 6);
    std::cout << "Score: ";
    rlutil::setColor(rlutil::LIGHTBLUE);
    std::cout << GoManager::points;

    // Draw game objects.
    for (i = 0; i < maxObj; i++)
    {
        if (lsr[i].visible && i < maxLsr)
        {
            lsr[i].draw();
        }
        if (ast[i].visible && i < maxAst)
        {
            ast[i].draw();
        }
        if (i < maxEny && eny[i].visible)
        {
            eny[i].draw();
        }
    }
}
