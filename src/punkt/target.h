#include <Gamebuino.h>

class Target
{
  public:
    Target();
    void moveToNewLocation();
    void draw(Gamebuino &gb);

  private:
    bool isTimeToDisplayHalo();
    byte _x;
    byte _y;
    byte _haloTimer;
};

