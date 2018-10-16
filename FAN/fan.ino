#include "Bun.h"
#include "Servo.h"

#define _pinRelay 8
#define _pinMosfet 9
#define _pinServo 10
#define _angleOpen 120
#define _angleClose 0

Bun _buttonPower(2, 100);
Bun _buttonStrength(3, 100);
Servo _servo;

bool _statePowerEnabled = false;
bool _stateStrengthHigh = false;

void setup()
{
  Serial.begin(9600);
  
  pinMode(_pinRelay, OUTPUT);
  pinMode(_pinMosfet, OUTPUT);
  _servo.attach(_pinServo);
  _servo.write(_angleClose);
  delay(500);
  _servo.detach();

  Serial.println("setup");
}

void loop()
{ 
  if (_buttonPower.onPressed()) 
  {
    _statePowerEnabled = !_statePowerEnabled;
    if (_statePowerEnabled)
    {
      _servo.attach(_pinServo);
      _servo.write(_angleOpen);
      delay(500);
      _servo.detach();              
      
      analogWrite(_pinMosfet, 255);
      
      Serial.println("ON");
    }
    else
    {
      analogWrite(_pinMosfet, 0);
      delay(1000);
      
      _servo.attach(_pinServo);
      _servo.write(_angleClose);
      delay(500);
      _servo.detach();             

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
