// akgvn - 2019/01
// CENG241 Term Project

#pragma once

#include <iostream>
#include <cstdlib>
#include "GameObject.h"
#include "Player.h"
#include "Laser.h"
#include "Asteroid.h"
#include "Enemy.h"

class GoManager
{
public:
  static Player p;
  static Enemy e;
  static void updateState(int);
  static void spawnLaser(int, int, int);
  static void spawnAsteroid(int, int);
  static void spawnEnemy(int, int);
  static void drawEverything();
  static void astController(int);
  static void enyController();

  static int activeAst; // Counts active asteroids.
  static int activeLsr; // Counts active lasers (enemy or friendly).
  static int activeEny; // Counts active enemies.
  static int maxObj;
  static int maxAst; // Maximum possible asteroids on screen.
  static int maxLsr; // Maximum possible lasers on screen.
  static int maxEny; // Maximum possible enemies on screen.
  static int points;
  static bool inGame;

  template <class A, class B>
  static bool collision(A &f, B &s)
  {
    // Collision detector
    if ((abs(f.getX() - s.getX()) <= 1) && (f.getY() == s.getY()))
    {
      if ((f.visible) && (s.visible))
      {
        f.destroy();
        s.destroy();
        return true;
      }
    }
    return false;
  }

private:
  static Asteroid *ast;
  static Laser *lsr;
  static Enemy *eny;
};