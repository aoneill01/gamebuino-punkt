#include <Gamebuino.h>

class Enemy
{
  public:
    Enemy();
    void update(unsigned long time);
    void draw(Gamebuino &gb) const;
    void spawn(unsigned long time);

  private:
    byte _x;
    byte _y;
    bool _horizontal;
    unsigned long _initTime;
};

