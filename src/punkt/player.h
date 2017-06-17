#include <Gamebuino.h>

class Player
{
  public:
    Player();
    void update(Gamebuino &gb);
    void draw(Gamebuino &gb) const;

  private:
    bool isTimeToMoveDiagonally();
    byte _x;
    byte _y;
    byte _diagonalTimer;
};

