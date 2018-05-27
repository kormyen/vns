#include "Inbound.h"
#include "Bun.h"

#define _pinLightMain 2
#define _pinLightKitchen 3
#define _pinLightOffice 4
#define _pinLightBed 5
#define _pinFanKitchen 6
#define _pinFanBed 7

Inbound _serialInput = Inbound();
Bun _buttonTestLights(38);

// State values stored as bool and float to remember prev value when toggled.
bool _stateLightMainEnabled = false;
float _stateLightMainValue = 1.0;
bool _stateLightKitchenEnabled = false;
float _stateLightKitchenValue = 1.0;
bool _stateLightOfficeEnabled = false;
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

  Serial.begin(9600);
  Serial.println("Enter data in this style: variable = value;");
  Serial.println("eg: lightMain = 50.5;");
  Serial.println("eg: lightMain = true;");
  Serial.println();
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
