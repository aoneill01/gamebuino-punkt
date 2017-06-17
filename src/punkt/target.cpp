#include "target.h"
#include "constants.h"

#define TARGET_SIZE 2

Target::Target() {
  moveToNewLocation();
}

void Target::moveToNewLocation() {
  _x = random(2, BOARD_WIDTH - TARGET_SIZE - 2);
  _y = random(2, BOARD_HEIGHT - TARGET_SIZE - 2);
}

void Target::draw(Gamebuino &gb) {
  gb.display.setColor(BLACK);
  gb.display.fillRect(_x, _y, TARGET_SIZE, TARGET_SIZE);

  if (isTimeToDisplayHalo()) {
    gb.display.setColor(GRAY);
    gb.display.drawFastHLine(_x - 1, _y - 2, 4);
    gb.display.drawFastHLine(_x - 1, _y + 3, 4);
    gb.display.drawFastVLine(_x - 2, _y - 1, 4);
    gb.display.drawFastVLine(_x + 3, _y - 1, 4);
  }
}

bool Target::isHit(byte x, byte y, byte s) const {
  return (x + s > _x) && (x < _x + TARGET_SIZE) && (y + s > _y) && (y < _y + TARGET_SIZE);
}

bool Target::isTimeToDisplayHalo() {
  _haloTimer++;
  return (_haloTimer & 0x08) != 0;
}

