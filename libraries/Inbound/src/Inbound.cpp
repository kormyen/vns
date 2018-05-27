#include "Inbound.h"

void Inbound::onFloatSet(OnFloatSetCallback callback)
{  
  _callbackOnFloatSet = callback;
}

void Inbound::onBoolSet(OnBoolSetCallback callback)
{  
  _callbackOnBoolSet = callback;
}

void Inbound::update()
{  
  recvWithStartEndMarkers();

  if (newData == true)
  {
      strcpy(tempChars, receivedChars); 
      // this temporary copy is necessary to protect the original data
      // because strtok() used in parseData() replaces the commas with \0
      parseData();
      newData = false;
  }
}

void Inbound::recvWithStartEndMarkers()
{
  static byte ndx = 0;
  char endMarker = ';';
  char rc;

  while (Serial.available() > 0 && newData == false)
  {
    rc = Serial.read();
    if (rc != endMarker)
    {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= NUMCHARS)
      {
        ndx = NUMCHARS - 1;
      }
    }
    else 
    {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void Inbound::parseData() 
{
  // https://stackoverflow.com/questions/3889992/how-does-strtok-split-the-string-into-tokens-in-c?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
  char* strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars," ");      // splits a C string into substrings, based on a separator character 
  _inputName = String(strtokIndx);
  
  strtokIndx = strtok(NULL, " "); // NULL as first value tells strtok to continue with last input and return next substring
  _marker = String(strtokIndx);

  if (String(_marker) == "=")
  {
    valid = true;
  }

  if (valid)
  {
    strtokIndx = strtok(NULL, " "); // NULL as first value tells strtok to continue with last input and return next substring
    _inputEnabled = String(strtokIndx);

    if (_inputEnabled == "true")
    {
      _callbackOnBoolSet(_inputName, true);
    }
    else if (_inputEnabled == "false")
    {
      _callbackOnBoolSet(_inputName, false);
    }
    else
    {
      // Set float
      _inputValue = atof(strtokIndx);     // converts a C string to a float
      _callbackOnFloatSet(_inputName, _inputValue);
    }
  }
}