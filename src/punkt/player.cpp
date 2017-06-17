#include "player.h"
#include "constants.h"

#define PLAYER_SIZE 4
#define DIAG_DELTA 91

Player::Player() {
  _x = (BOARD_WIDTH - PLAYER_SIZE) >> 1;
  _y = (BOARD_HEIGHT - PLAYER_SIZE) >> 1;
}

void Player::update(Gamebuino &gb) {
  if (gb.buttons.repeat(BTN_UP, 1)) {
    if (gb.buttons.repeat(BTN_LEFT, 1)) {
      if (isTimeToMoveDiagonally()) {
        if (_y > 0) _y--;
        if (_x > 0) _x--;
      }
    }
    else if (gb.buttons.repeat(BTN_RIGHT, 1)) {
      if (isTimeToMoveDiagonally()) {
        if (_y > 0) _y--;
        if (_x < BOARD_WIDTH - PLAYER_SIZE) _x++;
      }
    }
    else {
      if (_y > 0) _y--;
    }
  }
  else if (gb.buttons.repeat(BTN_DOWN, 1)) {
    if (gb.buttons.repeat(BTN_LEFT, 1)) {
      if (isTimeToMoveDiagonally()) {
        if (_y < BOARD_HEIGHT - PLAYER_SIZE) _y++;
        if (_x > 0) _x--;
      }
    }
    else if (gb.buttons.repeat(BTN_RIGHT, 1)) {
      if (isTimeToMoveDiagonally()) {
        if (_y < BOARD_HEIGHT - PLAYER_SIZE) _y++;
        if (_x < BOARD_WIDTH - PLAYER_SIZE) _x++;
      }
    }
    else {
      if (_y < BOARD_HEIGHT - PLAYER_SIZE) _y++;
    }
  }
  else if (gb.buttons.repeat(BTN_LEFT, 1)) {
    if (_x > 0) _x--;
  }
  else if (gb.buttons.repeat(BTN_RIGHT, 1)) {
    if (_x < BOARD_WIDTH - PLAYER_SIZE) _x++;
  }
}

void Player::draw(Gamebuino &gb) const {
  gb.display.setColor(BLACK, BLACK);
  gb.display.fillRect(_x + 1, _y, 2, PLAYER_SIZE); 
  gb.display.fillRect(_x, _y + 1, PLAYER_SIZE, 2); 
}

bool Player::isTimeToMoveDiagonally() {
  // 1/sqrt(2) approx eq to 91/128. If the high-order bit in a byte changes when adding 91, move diagonally.
  byte before = _diagonalTimer;
  _diagonalTimer += DIAG_DELTA;
  return (before & 0x80) != (_diagonalTimer & 0x80);
}

