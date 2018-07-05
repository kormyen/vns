#include "Inbound.h"
#include "Bun.h"

#define _pinLightMain 2
#define _pinLightKitchen 3
#define _pinLightOffice 4
#define _pinLightBed 5
#define _pinFanKitchen 6
#define _pinFanBed 7

// FANS SHOULD USE PIN PAIRS IF CHANGING PWM FREQ
// *   - Pins 5 and 6 are paired on timer0
// *   - Pins 9 and 10 are paired on timer1
// *   - Pins 3 and 11 are paired on timer2

Inbound _serialInput;
Bun _buttonTestLights(38);

// State values stored as bool and float to remember prev value when toggled.
bool _stateLightMainEnabled = true;
float _stateLightMainValue = 255.0;
bool _stateLightKitchenEnabled = false;
float _stateLightKitchenValue = 1.0;
bool _stateLightOfficeEnabled = true;
float _stateLightOfficeValue = 1.0;
bool _stateLightBedEnabled = false;
float _stateLightBedValue = 1.0;

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
  pinMode(_pinFanKitchen, OUTPUT);
  pinMode(_pinFanBed, OUTPUT);

  // Set higher PWM frequency for fan so stop audible motor whine.
  // Note that the base frequency for pins 5 and 6 is 62500 Hz
  // The divisors available on pins 5, 6, 9 and 10 are: 1, 8, 64, 256, 1024.
  // Source: https://playground.arduino.cc/Code/PwmFrequency
  setPwmFrequency(_pinFanKitchen, 8);

  Serial.begin(9600);
  Serial.println("Enter data in this style: variable = value;");
  Serial.println("eg: lightMain = 50.5;");
  Serial.println("eg: lightMain = true;");
  Serial.println();

  setCurrentState();
}

void loop()
{
  _serialInput.update();
  doTestLights();
  delay(30);
}

void handleFloatSet(String input, float value)
{
  if (input == "lightMain")
  {
    Serial.print("SET MAIN LIGHTS TO ");
    Serial.println(value);
    _stateLightMainValue = value;
  }
  else if (input == "lightKitchen")
  {
    Serial.print("SET KITCHEN LIGHTS TO ");
    Serial.println(value);
    _stateLightKitchenValue = value;
  }
  else if (input == "lightOffice")
  {
    Serial.print("SET OFFICE LIGHTS TO ");
    Serial.println(value);
    _stateLightOfficeValue = value;
  }
  else if (input == "lightBed")
  {
    Serial.print("SET BED LIGHTS TO ");
    Serial.println(value);
    _stateLightBedValue = value;
  }
  else if (input == "fanKitchen")
  {
    Serial.print("SET KITCHEN FAN TO ");
    Serial.println(value);
    _stateFanKitchenValue = value;
  }
  else if (input == "fanBed")
  {
    Serial.print("SET KITCHEN FAN TO ");
    Serial.println(value);
    _stateFanKitchenValue = value;
  }
  else
  {
    Serial.print("Not recognized: ");
    Serial.println(input);
  }

  setCurrentState();
}

void handleBoolSet(String input, bool value)
{
  if (input == "lightMain")
  {
    Serial.print("SET MAIN LIGHTS TO ");
    Serial.println(value);
    _stateLightMainEnabled = value;
  }
  else if (input == "lightKitchen")
  {
    Serial.print("SET KITCHEN LIGHTS TO ");
    Serial.println(value);
    _stateLightKitchenEnabled = value;
  }
  else if (input == "lightOffice")
  {
    Serial.print("SET OFFICE LIGHTS TO ");
    Serial.println(value);
    _stateLightOfficeEnabled = value;
  }
  else if (input == "lightBed")
  {
    Serial.print("SET BED LIGHTS TO ");
    Serial.println(value);
    _stateLightBedEnabled = value;
  }
  else if (input == "fanKitchen")
  {
    Serial.print("SET KITCHEN FAN TO ");
    Serial.println(value);
    _stateFanKitchenEnabled = value;
  }
  else if (input == "fanBed")
  {
    Serial.print("SET KITCHEN FAN TO ");
    Serial.println(value);
    _stateFanKitchenEnabled = value;
  }
  else
  {
    Serial.print("Not recognized: ");
    Serial.println(input);
  }

  setCurrentState();
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

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x07; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}
