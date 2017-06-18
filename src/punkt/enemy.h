#include <Gamebuino.h>

class Enemy
{
  public:
    Enemy();
    void update(unsigned long time);
    void draw(Gamebuino &gb) const;
    void spawn(unsigned long time);
    bool isHit(byte x, byte y, byte s) const;

  private:
    byte _x;
    byte _y;
    bool _horizontal;
    unsigned long _initTime;
};

