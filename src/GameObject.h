// akgvn - 2019/01
// CENG241 Term Project

#pragma once

#include <string>

class GameObject {
public:
  virtual void draw() = 0;
  GameObject();
  int getX();
  int getY();
  int getPX();
  int getPY();
  void setX(int);
  void setY(int);
  std::string sprite;
  bool visible;

protected:
  int size;
  int speed;

private:
  int x;
  int y;
  int prev_x;
  int prev_y;
};