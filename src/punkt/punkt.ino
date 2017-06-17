#include <SPI.h>
#include <Gamebuino.h>

#include "constants.h"
#include "enemy.h"
#include "player.h"

Gamebuino gb;
Player player;
Enemy enemy[10];

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
    
    gb.display.setColor(BLACK, BLACK);
    gb.display.fillRect(LCDWIDTH - GUTTER_WIDTH, 0, GUTTER_WIDTH, BOARD_HEIGHT);

    gb.display.setFont(font3x5);
    gb.display.setColor(WHITE);
    gb.display.cursorX = BOARD_WIDTH + 1;
    gb.display.cursorY = 1;
    gb.display.print("01");
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

