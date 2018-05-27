#include "Arduino.h"

#define NUMCHARS 32

typedef void (*OnFloatSetCallback)(String, float);
typedef void (*OnBoolSetCallback)(String, bool);

class Inbound
{
  public:
    void onFloatSet(OnFloatSetCallback);
    void onBoolSet(OnBoolSetCallback);
    void update();
  private:
    OnFloatSetCallback _callbackOnFloatSet;
    OnBoolSetCallback _callbackOnBoolSet;
    String _inputName;
    float _inputValue;
    String _inputEnabled;
    String _marker;
    char receivedChars[NUMCHARS];
    char tempChars[NUMCHARS];
    boolean newData = false;
    bool valid = false;
    void recvWithStartEndMarkers();
    void parseData();
};