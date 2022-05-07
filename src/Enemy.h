// akgvn - 2019/01
// CENG241 Term Project

#pragma once

#include "GameObject.h"

class Enemy : public GameObject
{
public:
  Enemy();
  Enemy(int, int);
  int health;
  void update(int);
  void draw();
  void destroy();
  void fire();
  void death();
};