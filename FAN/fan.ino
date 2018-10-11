#include "Bun.h"

#define _pinRelay 2
#define _pinMosfet 3

Bun _buttonPower(8, 100);
Bun _buttonStrength(9, 100);

bool _statePowerEnabled = false;
bool _stateStrengthHigh = false;

void setup()
{
  Serial.begin(9600);
  
  pinMode(_pinRelay, OUTPUT);
  pinMode(_pinMosfet, OUTPUT);

  Serial.println("setup");
}

void loop()
{
  if (_buttonPower.onPressed()) 
  {
    _statePowerEnabled = !_statePowerEnabled;
    
    
    if (_statePowerEnabled)
    {
      analogWrite(_pinMosfet, 255);
      Serial.println("ON");
    }
    else
    {
      analogWrite(_pinMosfet, 0);
      Serial.println("OFF");
    }
  }
  
  if (_buttonStrength.onPressed()) 
  {
    _stateStrengthHigh = !_stateStrengthHigh;
    digitalWrite(_pinRelay, _stateStrengthHigh);
    
    Serial.print("high: ");
    Serial.println(_stateStrengthHigh);
  }
}
