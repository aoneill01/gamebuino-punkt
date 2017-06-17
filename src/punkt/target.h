#include <Gamebuino.h>

class Target
{
  public:
    Target();
    void moveToNewLocation();
    void draw(Gamebuino &gb);
    bool isHit(byte x, byte y, byte s) const;

  private:
    bool isTimeToDisplayHalo();
    byte _x;
    byte _y;
    byte _haloTimer;
};

