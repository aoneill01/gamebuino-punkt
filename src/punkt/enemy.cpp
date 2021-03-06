#include "enemy.h"
#include "constants.h"

#define ENEMY_SIZE 2
#define SLOW_DISTANCE 16
#define SLOW_TIME 64
#define HORIZ_CONST_TIME BOARD_WIDTH - ENEMY_SIZE - 2 * SLOW_DISTANCE
#define VERT_CONST_TIME BOARD_HEIGHT - ENEMY_SIZE - 2 * SLOW_DISTANCE

Enemy::Enemy() {
  
}

void Enemy::update(unsigned long time) {
  if (_horizontal) {
    int t = (time - _initTime) % (HORIZ_CONST_TIME + HORIZ_CONST_TIME + SLOW_TIME + SLOW_TIME);
    if (t < HORIZ_CONST_TIME) {
      _x = SLOW_DISTANCE + t;
    }
    else if (t < HORIZ_CONST_TIME + SLOW_TIME) {
      t -= HORIZ_CONST_TIME;
      _x = -1 * ((t * t) >> 6) + t + SLOW_DISTANCE + HORIZ_CONST_TIME;
    }
    else if (t < HORIZ_CONST_TIME + HORIZ_CONST_TIME + SLOW_TIME)
    {
      t -= HORIZ_CONST_TIME + SLOW_TIME;
      _x = SLOW_DISTANCE + HORIZ_CONST_TIME - t;
    }
    else
    {
      t -= HORIZ_CONST_TIME + HORIZ_CONST_TIME + SLOW_TIME;
      _x = ((t * t) >> 6) - t + SLOW_DISTANCE;
    }
  }
  else {
    int t = (time - _initTime) % (VERT_CONST_TIME + VERT_CONST_TIME + SLOW_TIME + SLOW_TIME);
    if (t < VERT_CONST_TIME) {
      _y = SLOW_DISTANCE + t;
    }
    else if (t < VERT_CONST_TIME + SLOW_TIME) {
      t -= VERT_CONST_TIME;
      _y = -1 * ((t * t) >> 6) + t + SLOW_DISTANCE + VERT_CONST_TIME;
    }
    else if (t < VERT_CONST_TIME + VERT_CONST_TIME + SLOW_TIME)
    {
      t -= VERT_CONST_TIME + SLOW_TIME;
      _y = SLOW_DISTANCE + VERT_CONST_TIME - t;
    }
    else
    {
      t -= VERT_CONST_TIME + VERT_CONST_TIME + SLOW_TIME;
      _y = ((t * t) >> 6) - t + SLOW_DISTANCE;
    }
  }
}

void Enemy::draw(Gamebuino &gb) const {
  gb.display.setColor(BLACK);
  gb.display.fillRect(_x, _y, ENEMY_SIZE, ENEMY_SIZE);  
}

void Enemy::spawn(unsigned long time, byte playerX, byte playerY) {
  _horizontal = random(BOARD_WIDTH + BOARD_HEIGHT) < BOARD_HEIGHT;
  
  if (_horizontal) {
    _y = random(BOARD_HEIGHT - ENEMY_SIZE);
    _initTime = time - (HORIZ_CONST_TIME + (SLOW_TIME >> 1));
    // Make sure it doesn't spawn close to the player
    if (playerX > (BOARD_WIDTH >> 1)) {
      _initTime -= HORIZ_CONST_TIME + SLOW_TIME;
    }
  }
  else {
    _x = random(BOARD_WIDTH - ENEMY_SIZE);
    _initTime = time - (VERT_CONST_TIME + (SLOW_TIME >> 1));
    // Make sure it doesn't spawn close to the player
    if (playerY > (BOARD_HEIGHT >> 1)) {
      _initTime -= VERT_CONST_TIME + SLOW_TIME;
    }
  }
  
  update(time);
}

bool Enemy::isHit(byte x, byte y, byte s) const {
  return (x + s > _x) && (x < _x + ENEMY_SIZE) && (y + s > _y) && (y < _y + ENEMY_SIZE);
}
