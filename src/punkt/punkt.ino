#include <SPI.h>
#include <Gamebuino.h>

#include "constants.h"
#include "enemy.h"
#include "player.h"
#include "target.h"

#define MAX_ENEMIES 50

#define MODE_PLAYING 0
#define MODE_GAME_OVER 1

Gamebuino gb;
// Represents the player
Player player;
// Represents the obstacles to avoid
Enemy enemies[MAX_ENEMIES];
byte enemyCount;
// Represents what the player is trying to capture
Target target;
byte score;
byte highScore;
byte mode;

extern const byte font3x5[];

void setup() {
  gb.begin();
  gb.pickRandomSeed();
  reset();
}

void loop() {
  if (gb.update()) {
    if (gb.buttons.pressed(BTN_C)) reset();

    switch (mode) {
      case MODE_PLAYING:
        doPlaying();
        break;
      case MODE_GAME_OVER:
        doGameOver();
        break;
    }    
  }
}

void reset() {
  gb.titleScreen(F("punkt"));
  gb.setFrameRate(30);
  gb.battery.show = false;

  initializeGame();
}

void initializeGame() {
  enemyCount = 0;
  score = 0;
  player = Player();
  target = Target();
  mode = MODE_PLAYING;
}

void doPlaying() {
  player.update(gb);
  
  for (byte i = 0; i < enemyCount; i++) 
  {
    enemies[i].update(gb.frameCount);
    if (enemies[i].isHit(player.getX(), player.getY(), 4)) mode = MODE_GAME_OVER;
  }

  if (target.isHit(player.getX(), player.getY(), 4)) {
    target.moveToNewLocation();
    if (enemyCount < MAX_ENEMIES) {
      enemies[enemyCount++].spawn(gb.frameCount);
    }
    if (score < 100) score++;
    if (score > highScore) highScore = score;
  }

  drawBoard();
}

void doGameOver() {
  drawBoard();

  gb.display.setColor(BLACK);
  if (gb.frameCount & 0x08) drawScore();
  gb.display.fillRect((BOARD_WIDTH - ((4 * 9) + 1)) >> 1, (BOARD_HEIGHT - 7) >> 1, (4 * 9) + 1, 7);
  gb.display.setFont(font3x5);
  gb.display.setColor(WHITE);
  gb.display.cursorX = ((BOARD_WIDTH - (4 * 9) + 1) >> 1);
  gb.display.cursorY = ((BOARD_HEIGHT - 7) >> 1) + 1;
  gb.display.print("Game Over");

  if (gb.buttons.pressed(BTN_A) || gb.buttons.pressed(BTN_B)) initializeGame();
}

void drawBoard() {
  target.draw(gb);
  
  player.draw(gb);

  for (byte i = 0; i < enemyCount; i++) 
  {
    enemies[i].draw(gb);
  }
  
  drawGutter();
}

void drawGutter() {
  gb.display.setColor(BLACK);
  gb.display.fillRect(LCDWIDTH - GUTTER_WIDTH, 0, GUTTER_WIDTH, BOARD_HEIGHT);

  gb.display.setColor(WHITE);
  drawScore();
  drawHighScore();
}

void drawScore() {
  gb.display.setFont(font3x5);
  gb.display.cursorX = BOARD_WIDTH + 1;
  gb.display.cursorY = 1;
  if (score < 10) gb.display.print('0');
  gb.display.print(score);
}

void drawHighScore() {
  gb.display.setFont(font3x5);
  gb.display.cursorX = BOARD_WIDTH + 1;
  gb.display.cursorY = BOARD_HEIGHT - 12;
  gb.display.print("hi");
  gb.display.cursorX = BOARD_WIDTH + 1;
  gb.display.cursorY = BOARD_HEIGHT - 6;
  if (highScore < 10) gb.display.print('0');
  gb.display.print(highScore);
}

