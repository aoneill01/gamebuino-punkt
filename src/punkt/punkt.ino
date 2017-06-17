#include <SPI.h>
#include <Gamebuino.h>

#include "constants.h"
#include "enemy.h"
#include "player.h"
#include "target.h"

#define MAX_ENEMIES 50

Gamebuino gb;
// Represents the player
Player player;
// Represents the obstacles to avoid
Enemy enemies[MAX_ENEMIES];
byte enemyCount;
// Represents what the player is trying to capture
Target target;
byte score;

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

    for (byte i = 0; i < enemyCount; i++) 
    {
      enemies[i].update(gb.frameCount);
      enemies[i].draw(gb);
    }

    player.draw(gb);

    target.draw(gb);
    if (target.isHit(player.getX(), player.getY(), 4)) {
      target.moveToNewLocation();
      if (enemyCount < MAX_ENEMIES) {
        enemies[enemyCount++].spawn(gb.frameCount);
      }
      if (score < 100) score++;
    }

    drawGutter();
  }
}

void reset() {
  gb.titleScreen(F("punkt"));
  gb.setFrameRate(30);
  gb.battery.show = false;
  enemyCount = 0;
  score = 0;
  player = Player();
  target = Target();
}

void drawGutter() {
  gb.display.setColor(BLACK, BLACK);
  gb.display.fillRect(LCDWIDTH - GUTTER_WIDTH, 0, GUTTER_WIDTH, BOARD_HEIGHT);

  gb.display.setFont(font3x5);
  gb.display.setColor(WHITE);
  gb.display.cursorX = BOARD_WIDTH + 1;
  gb.display.cursorY = 1;
  if (score < 10) gb.display.print("0");
  gb.display.print(String(score));
}

