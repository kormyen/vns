int val = 0;
bool buttonState = false;
int lastTime = 0;
int minTime = 5;

void setup()
{
  Serial.begin(9600);
  Serial.println("start");
  pinMode(10, INPUT_PULLUP);
}

void loop()
{
  val = digitalRead(10);

  if (val == LOW)
  {
    if (!buttonState)
    {
      if ((millis() - lastTime) > minTime)
      {
        lastTime = millis();
        Serial.print("down ");
        Serial.println(millis());
        buttonState = true;
      }
    }
    
  } 
  else 
  {
    if (buttonState)
    {
      if ((millis() - lastTime) > minTime)
      {
        lastTime = millis();
        Serial.print("up ");
        Serial.println(millis());
        buttonState = false;
      }
    }
    
  }
}
