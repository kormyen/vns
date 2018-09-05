#include <Arduino.h>

class Bun
{
  public:
    Bun(int pin);
    Bun(int pin, int minDelay);
    bool isPressed();
    bool isReleased();
    bool onPressed();
    bool onReleased();
  private:
    int _pin;
    int _minDelay = -1;
    int _lastTime = 0;
    bool _prevState = false;
    bool _onPressedDone  = false;
    bool _onReleasedDone = false;
    bool getState();
};