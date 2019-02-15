// akgvn - 2019/01
// CENG241 Term Project

#include "GameObject.h"

GameObject::GameObject()
{
    x = 1;
    y = 1;
    prev_x = 1;
    prev_y = 1;
    speed = 1;
    size = 1;
    visible = false;
}

int GameObject::getX() { return x; }
int GameObject::getY() { return y; }
int GameObject::getPX() { return prev_x; }
int GameObject::getPY() { return prev_y; }

void GameObject::setX(int n)
{
    prev_x = x;
    x = n;
}

void GameObject::setY(int n)
{
    prev_y = y;
    y = n;
}