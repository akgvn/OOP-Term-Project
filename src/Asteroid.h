// akgvn - 2019/01
// CENG241 Term Project

#pragma once

#include "GameObject.h"

class Asteroid : public GameObject {
public:
    Asteroid();
    Asteroid(int, int);
    int health;
    void update();
    void draw();
    void destroy();
};