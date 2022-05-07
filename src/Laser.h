// akgvn - 2019/01
// CENG241 Term Project

#pragma once

#include "GameObject.h"

class Laser : public GameObject
{
public:
  Laser();
  void move();
  void update();
  void draw();
  int direction;
  void destroy();
};