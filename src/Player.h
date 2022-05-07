// akgvn - 2019/01
// CENG241 Term Project

#pragma once

#include <string>

#include "GameObject.h"
#include "Laser.h"

class Player : public GameObject {
public:
    Player();
    int health;
    void draw();
    void update();
    void destroy();

private:
    void fire();
    void death();
};