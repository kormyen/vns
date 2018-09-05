#include "Bun.h"

#define DELAY 10
#define pinA 2
#define pinB 3

volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
int encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
int oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

Bun _buttonOne(4, DELAY);
Bun _buttonTwo(5, DELAY);
Bun _buttonThree(6, DELAY);
Bun _buttonFour(7, DELAY);

Bun _buttonFive(8, DELAY);
Bun _buttonSix(9, DELAY);
Bun _buttonSeven(10, DELAY);
Bun _buttonEight(11, DELAY);
Bun _buttonPot(12, DELAY);

void setup()
{
  Serial.begin(9600);
  Serial.println("start");

  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  // https://www.instructables.com/id/Improved-Arduino-Rotary-Encoder-Reading/
  attachInterrupt(0,PinA,RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(1,PinB,RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)
}

void PinA()
{
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  if(reading == B00001100 && aFlag)
  { 
    //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos --; //decrement the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00000100) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

void PinB()
{
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B00001100 && bFlag) 
  { 
    //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //increment the encoder's position count
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00001000) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

void loop()
{
  if(oldEncPos != encoderPos)
  {
    Serial.println(encoderPos);
    oldEncPos = encoderPos;
  }

  if (_buttonOne.onPressed()) { Serial.println("1+"); }
  else if (_buttonOne.onReleased()) { Serial.println("1-"); }
  
  else if (_buttonTwo.onPressed()) { Serial.println("2+"); }
  else if (_buttonTwo.onReleased()) { Serial.println("2-"); }
  
  else if (_buttonThree.onPressed()) { Serial.println("3+"); }
  else if (_buttonThree.onReleased()) { Serial.println("3-"); }
  
  else if (_buttonFour.onPressed()) { Serial.println("4+"); }
  else if (_buttonFour.onReleased()) { Serial.println("4-"); }

  else if (_buttonFive.onPressed()) { Serial.println("5+"); }
  else if (_buttonFive.onReleased()) { Serial.println("5-"); }

  else if (_buttonSix.onPressed()) { Serial.println("6+"); }
  else if (_buttonSix.onReleased()) { Serial.println("6-"); }

  else if (_buttonSeven.onPressed()) { Serial.println("7+"); }
  else if (_buttonSeven.onReleased()) { Serial.println("7-"); }

  else if (_buttonEight.onPressed()) { Serial.println("8+"); }
  else if (_buttonEight.onReleased()) { Serial.println("8-"); }

  else if (_buttonPot.onPressed()) { Serial.println("O+"); }
  else if (_buttonPot.onReleased()) { Serial.println("O-"); }
}
