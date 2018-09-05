#include "Bun.h"

#define DELAY 10

Bun _buttonOne(2, DELAY);
Bun _buttonTwo(4, DELAY);
Bun _buttonThree(5, DELAY);
Bun _buttonFour(3, DELAY);

Bun _buttonFive(8, DELAY);
Bun _buttonSix(6, DELAY);
Bun _buttonSeven(9, DELAY);
Bun _buttonEight(7, DELAY);

Bun _buttonPen(10, DELAY);

void setup()
{
  Serial.begin(9600);
  Serial.println("start");
}

void loop()
{
  if (_buttonOne.onPressed()) { Serial.println("1 ^"); }
  else if (_buttonOne.onReleased()) { Serial.println("1 V"); }
  
  else if (_buttonTwo.onPressed()) { Serial.println("2 ^"); }
  else if (_buttonTwo.onReleased()) { Serial.println("2 V"); }
  
  else if (_buttonThree.onPressed()) { Serial.println("3 ^"); }
  else if (_buttonThree.onReleased()) { Serial.println("3 V"); }
  
  else if (_buttonFour.onPressed()) { Serial.println("4 ^"); }
  else if (_buttonFour.onReleased()) { Serial.println("4 V"); }

  else if (_buttonFive.onPressed()) { Serial.println("5 ^"); }
  else if (_buttonFive.onReleased()) { Serial.println("5 V"); }

  else if (_buttonSix.onPressed()) { Serial.println("6 ^"); }
  else if (_buttonSix.onReleased()) { Serial.println("6 V"); }

  else if (_buttonSeven.onPressed()) { Serial.println("7 ^"); }
  else if (_buttonSeven.onReleased()) { Serial.println("7 V"); }

  else if (_buttonEight.onPressed()) { Serial.println("8 ^"); }
  else if (_buttonEight.onReleased()) { Serial.println("8 V"); }

  else if (_buttonPen.onPressed()) { Serial.println("O ^"); }
  else if (_buttonPen.onReleased()) { Serial.println("O V"); }
}
