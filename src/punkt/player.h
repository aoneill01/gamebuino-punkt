#include <Gamebuino.h>

class Player
{
  public:
    Player();
    void update(Gamebuino &gb);
    void draw(Gamebuino &gb) const;
    byte getX() const { return _x; }
    byte getY() const { return _y; }

  private:
    bool isTimeToMoveDiagonally();
    byte _x;
    byte _y;
    byte _diagonalTimer;
};

