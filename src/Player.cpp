// akgvn - 2019/01
// CENG241 Term Project

#include "GameObject.h"
#include "Player.h"
#include "rlutil.h"
#include "GoManager.h"
#include <iostream>

using namespace rlutil;

Player::Player() {
    visible = true;
    sprite = "#+";
    size = 2;
    health = 3;

    // Default positions.
    setX(3);
    setY(10);
}

void Player::draw() {
    // Delete the after image.
    locate(getPX(), getPY());
    std::cout << "  ";

    // Player ship is blue.
    setColor(LIGHTBLUE);

    // If the player is dead, draw the ship in red.
    if (health == 0) {
        setColor(RED);
    }

    // Draw the player ship.
    locate(getX(), getY());
    std::cout << sprite;

    // Reset the color.
    setColor(GREY);
}

void Player::update() {
    int k;

    if (health <= 0) {
        death();
    }

    // Check for player input.
    if (kbhit()) {
        k = getkey();

        if (k == KEY_UP && getY() > 1) {
            // Move up.
            setY(getY() - 1);
            setX(getX());
        }
        else if (k == KEY_DOWN && getY() < 25) {
            // Move down.
            setY(getY() + 1);
            setX(getX());
        }
        else if (k == KEY_LEFT && getX() > 1) {
            // Move left.
            setX(getX() - 1);
            setY(getY());
        }
        else if (k == KEY_RIGHT && getX() < 79) {
            // Move right.
            setX(getX() + 1);
            setY(getY());
        }
        else if (k == KEY_SPACE) {
            // Fire, spawn laser.
            fire();
        }
    }
}

void Player::fire() {
    // Spawn a laser that goes right.
    GoManager::spawnLaser(this->getX() + size, this->getY(), 1);
}

void Player::destroy() {
    // This gets called when player collides with another game object. Health goes down.
    this->health -= 1;

    if (health <= 0) {
        death();
    }
}

void Player::death() {
    // When player dies, game ends.
    GoManager::inGame = false;
}