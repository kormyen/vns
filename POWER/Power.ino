#include "Inbound.h"
#include "Bun.h"

#define _pinLightMain 2
#define _pinLightKitchen 3
#define _pinLightOffice 4
#define _pinLightBed 5

// Fans should be on pins 6, 7, and/or 8 due to PWM freq adjustments to stop audible motor whine.
#define _pinFanKitchen 6
#define _pinFanBed 7

#define _fanMinValue 170

Inbound _serialInput;
Bun _buttonTestLights(38);

// State values stored as bool and float to remember prev value when toggled.
bool _stateLightMainEnabled = true;
float _stateLightMainValue = 255.0;
bool _stateLightKitchenEnabled = false;
float _stateLightKitchenValue = 1.0;
bool _stateLightOfficeEnabled = true;
float _stateLightOfficeValue = 50.0;
bool _stateLightBedEnabled = true;
float _stateLightBedValue = 150.0;

bool _stateFanKitchenEnabled = false;
float _stateFanKitchenValue = 1.0;
bool _stateFanBedEnabled = false;
float _stateFanBedValue = 1.0;

void setup()
{
  _serialInput.onFloatSet(handleFloatSet);
  _serialInput.onBoolSet(handleBoolSet);

  pinMode(_pinLightMain, OUTPUT);
  pinMode(_pinLightKitchen, OUTPUT);
  pinMode(_pinLightOffice, OUTPUT);
  pinMode(_pinLightBed, OUTPUT);

  setFanPwmFreq();
  pinMode(_pinFanKitchen, OUTPUT);
  pinMode(_pinFanBed, OUTPUT);

  Serial.begin(9600);

  setCurrentState();
}

void loop()
{
  _serialInput.update();
  doTestLights();
  delay(30);
}

void response(bool value)
{
  if (value)
  {
    Serial.println("y");
  }
  else
  {
    Serial.println("n");
  }
}

void setFanPwmFreq()
{
  /* Source: valerio_sperati https://forum.arduino.cc/index.php?topic=72092.0
   * Set higher PWM frequency for fan so stop audible motor whine.
   * FANS SHOULD USE PIN PAIRS IF CHANGING PWM FREQ
   * On Arduino Mega 2560:
   * timer 0 (controls pin 13, 4);
   * timer 1 (controls pin 12, 11);
   * timer 2 (controls pin 10, 9);
   * timer 3 (controls pin 5, 3, 2);
   * timer 4 (controls pin 8, 7, 6);
   * 'TCCRnB' is the timer register id (or similar) where 'n' = timer # above.
   * eg: 'TCCR4B' is for pins 8, 7, 6.
  */
  int myEraser = 7; // this is 111 in binary and is used as an eraser
  TCCR4B &= ~myEraser; // this operation (AND plus NOT),  set the three bits in TCCR2B to 0

  /* TCCR1B, TCCR2B, TCCR3B, TCCR4B
   * prescaler = 1 ---> PWM frequency is 31000 Hz
   * prescaler = 2 ---> PWM frequency is 4000 Hz
   * prescaler = 3 ---> PWM frequency is 490 Hz (default value)
   * prescaler = 4 ---> PWM frequency is 120 Hz
   * prescaler = 5 ---> PWM frequency is 30 Hz
   * prescaler = 6 ---> PWM frequency is <20 Hz
   * 
   * TCCR0B. Note: if altering timer 0 delay() millis() etc will change speed.
   * prescaler = 1 ---> PWM frequency is 62000 Hz
   * prescaler = 2 ---> PWM frequency is 7800 Hz
   * prescaler = 3 ---> PWM frequency is 980 Hz (default value)
   * prescaler = 4 ---> PWM frequency is 250 Hz
   * prescaler = 5 ---> PWM frequency is 60 Hz
   * prescaler = 6 ---> PWM frequency is <20 Hz
   */
  int myPrescaler = 1; // this could be a number in [1 , 6].
  TCCR4B |= myPrescaler; //this operation (OR), replaces the last three bits in TCCR2B with our new value 011
}

void handleFloatSet(String input, float value)
{
  if (input == "lMainB")
  {
    _stateLightMainValue = value;
  }
  else if (input == "lKitchenB")
  {
    _stateLightKitchenValue = value;
  }
  else if (input == "lOfficeB")
  {
    _stateLightOfficeValue = value;
  }
  else if (input == "lBedB")
  {
    _stateLightBedValue = value;
  }
  else if (input == "fKitchenS")
  {
    _stateFanKitchenValue = map(value, 0, 255, _fanMinValue, 255);
  }
  else if (input == "fBedS")
  {
    _stateFanBedValue = map(value, 0, 255, _fanMinValue, 255);
  }
  else
  {
    response(false);
  }

  setCurrentState();
  response(true);
}

void handleBoolSet(String input, bool value)
{
  if (input == "lMain")
  {
    _stateLightMainEnabled = value;
  }
  else if (input == "lKitchen")
  {
    _stateLightKitchenEnabled = value;
  }
  else if (input == "lOffice")
  {
    _stateLightOfficeEnabled = value;
  }
  else if (input == "lBed")
  {
    _stateLightBedEnabled = value;
  }
  else if (input == "fKitchen")
  {
    _stateFanKitchenEnabled = value;
  }
  else if (input == "fBed")
  {
    _stateFanBedEnabled = value;
  }
  else
  {
    response(false);
  }

  setCurrentState();
  response(true);
}

void setCurrentState()
{
  digitalWrite(LED_BUILTIN, _stateLightMainEnabled);

  // LIGHT MAIN
  if (_stateLightMainEnabled)
  {
    analogWrite(_pinLightMain, _stateLightMainValue);
  }
  else
  {
    analogWrite(_pinLightMain, 0);
  }

  // LIGHT KITCHEN
  if (_stateLightKitchenEnabled)
  {
    analogWrite(_pinLightKitchen, _stateLightKitchenValue);
  }
  else
  {
    analogWrite(_pinLightKitchen, 0);
  }

  // LIGHT OFFICE
  if (_stateLightOfficeEnabled)
  {
    analogWrite(_pinLightOffice, _stateLightOfficeValue);
  }
  else
  {
    analogWrite(_pinLightOffice, 0);
  }

  // LIGHT BED
  if (_stateLightBedEnabled)
  {
    analogWrite(_pinLightBed, _stateLightBedValue);
  }
  else
  {
    analogWrite(_pinLightBed, 0);
  }

  // FAN KITCHEN
  if (_stateFanKitchenEnabled)
  {
    analogWrite(_pinFanKitchen, _stateFanKitchenValue);
  }
  else
  {
    analogWrite(_pinFanKitchen, 0);
  }

  // FAN BED
  if (_stateFanBedEnabled)
  {
    analogWrite(_pinFanBed, _stateFanBedValue);
  }
  else
  {
    analogWrite(_pinFanBed, 0);
  }
}

// Toggle button for testing. Switches all lights on/off.
void doTestLights()
{
  if (_buttonTestLights.onPressed())
  {
    if (!_stateLightMainEnabled)
    {
      _stateLightMainEnabled = true;
      _stateLightMainValue = 100;
      _stateLightKitchenEnabled = true;
      _stateLightKitchenValue = 100;
      _stateLightOfficeEnabled = true;
      _stateLightOfficeValue = 100;
      _stateLightBedEnabled = true;
      _stateLightBedValue = 100;
    }
    else
    {
      _stateLightMainEnabled = false;
      _stateLightKitchenEnabled = false;
      _stateLightOfficeEnabled = false;
      _stateLightBedEnabled = false;
    }

    setCurrentState();
  }
}
