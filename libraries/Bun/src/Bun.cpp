#include <Arduino.h>
#include <Bun.h>

Bun::Bun(int pin)
{
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);
}

Bun::Bun(int pin, int minDelay)
{
  _pin = pin;
  _minDelay = minDelay;
  pinMode(_pin, INPUT_PULLUP);
}

bool Bun::isPressed()
{
  return getState();
}

bool Bun::isReleased()
{
  return !isPressed();
}

bool Bun::onPressed()
{
  if(isPressed())
  {
    if(!_onPressedDone)
    {
      return _onPressedDone = true;
    }
    return false;
  }
  // else
  _onPressedDone = false;
  return false;
}

bool Bun::onReleased()
{
  if(isReleased())
  {
    if(!_onReleasedDone)
    {
      return _onReleasedDone = true;
    }
    return false;
  }
  // else isPressed()
  _onReleasedDone = false;
  return false;
}

bool Bun::getState()
{
  if (_minDelay == -1)
  {
    // Simple button
    return !digitalRead(_pin);
  }
  else
  {
    // Button with delay time
    if ((millis() - _lastTime) > _minDelay)
    {
      // Delay time expired so update state
      _lastTime = millis();
      _prevState = !digitalRead(_pin);
    }
    return _prevState;
  }
}