#include <SPI.h>
#include <Gamebuino.h>

#include "constants.h"
#include "enemy.h"
#include "player.h"
#include "target.h"

Gamebuino gb;
// Represents the player
Player player;
// Represents the obstacles to avoid
Enemy enemy[10];
// Represents what the player is trying to capture
Target target;

extern const byte font3x5[];

void setup() {
  gb.begin();
  gb.pickRandomSeed();
  reset();
}

void loop() {
  if (gb.update()) {
    if (gb.buttons.pressed(BTN_C)) reset();
    player.update(gb);

    for (byte i = 0; i < 10; i++) 
    {
      enemy[i].update(gb.frameCount + i * 30);
      enemy[i].draw(gb);
    }

    player.draw(gb);

    target.draw(gb);
    // target.moveToNewLocation();

    drawGutter();
  }
}

void reset() {
  gb.titleScreen(F("punkt"));
  gb.setFrameRate(30);
  gb.battery.show = false;
  for (byte i = 0; i < 10; i++) 
  {
    enemy[i].setHorizontal(i % 2);
    enemy[i].setY(i * 4 + 1);
    enemy[i].setX(i * 4 + 1);
  }
}

void drawGutter() {
  gb.display.setColor(BLACK, BLACK);
  gb.display.fillRect(LCDWIDTH - GUTTER_WIDTH, 0, GUTTER_WIDTH, BOARD_HEIGHT);

  gb.display.setFont(font3x5);
  gb.display.setColor(WHITE);
  gb.display.cursorX = BOARD_WIDTH + 1;
  gb.display.cursorY = 1;
  gb.display.print("01");
}

