#include <Gamebuino.h>

class Enemy
{
  public:
    Enemy();
    void update(unsigned long time);
    void draw(Gamebuino &gb) const;
    void setY(byte y) { _y = y; }
    void setX(byte x) { _x = x; }
    void setHorizontal(bool horizontal) { _horizontal = horizontal; }
    bool isHorizontal() { return _horizontal; }

  private:
    byte _x;
    byte _y;
    bool _horizontal;
};

