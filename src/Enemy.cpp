// akgvn - 2019/01
// CENG241 Term Project

#include "Enemy.h"

#include "rlutil.h"
#include "GoManager.h"

using namespace std;
using namespace rlutil;

Enemy::Enemy()
{
    sprite = "<?";
    health = 2;
}

Enemy::Enemy(int nx, int ny)
{
    sprite = "<?";
    health = 2;
    setX(nx);
    setY(ny);
}

void Enemy::update(int frame)
{
    if (health > 0)
    {
        if (getX() == 1)
        {
            destroy();
            return;
        }

        setX(getX() - 1);
        setY(getY());

        if (frame % 30 == 0) // Fire every 30 frames
            fire();
    }
    else
        destroy();
}
void Enemy::draw()
{
    // If enemy has health, draw it.
    if (health)
    {
        setColor(LIGHTMAGENTA);

        // Clear the after image.
        locate(getPX(), getPY());
        cout << "  ";

        // Draw the enemy.
        locate(getX(), getY());
        cout << sprite;

        // Reset the color.
        setColor(GREY);
    }
}

void Enemy::destroy()
{
    this->health -= 1;
    if (health <= 0)
        death();
}

void Enemy::fire()
{
    GoManager::spawnLaser(this->getX() - (size + 1), this->getY(), -1);
}

void Enemy::death()
{
    health = 0;
    visible = false;

    // Clear the after image.
    locate(getPX(), getPY());
    cout << "  ";
    locate(getX(), getY());
    cout << "  ";

    // Inform the manager.
    GoManager::activeEny--;
    GoManager::points += 2;
}