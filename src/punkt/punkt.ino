#include <SPI.h>
#include <Gamebuino.h>
#include "enemy.h"
#include "constants.h"

Gamebuino gb;
Enemy enemy[10];

extern const byte font3x5[];

const byte player[] PROGMEM = { 8, 8, 
  B00000000,
  B00000000,
  B00011000,
  B00111100,
  B00111100,
  B00011000,
  B00000000,
  B00000000};

byte playerX = 1;
byte playerY = 1;

void setup() {
  gb.begin();
  gb.pickRandomSeed();
  reset();
}

void loop() {
  if (gb.update()) {
    if (gb.buttons.pressed(BTN_C)) reset();
    if (gb.buttons.repeat(BTN_UP, 1)) playerY--;
    if (gb.buttons.repeat(BTN_DOWN, 1)) playerY++;
    if (gb.buttons.repeat(BTN_LEFT, 1)) playerX--;
    if (gb.buttons.repeat(BTN_RIGHT, 1)) playerX++;

    gb.display.setColor(BLACK, BLACK);
    gb.display.fillRect(LCDWIDTH - GUTTER_WIDTH, 0, GUTTER_WIDTH, BOARD_HEIGHT);

    gb.display.drawBitmap(playerX, playerY, player);

    gb.display.setFont(font3x5);
    gb.display.setColor(WHITE);
    gb.display.cursorX = LCDWIDTH - GUTTER_WIDTH + 1;
    gb.display.cursorY = 1;
    gb.display.print("01");

    for (byte i = 0; i < 10; i++) 
    {
      enemy[i].update(gb.frameCount + i * 30);
      enemy[i].draw(gb);
    }
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

