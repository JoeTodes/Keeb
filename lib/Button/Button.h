#ifndef Button_h
#define Button_h

#include "Arduino.h"
#include "HID-Project.h"

typedef void (*ButtonCallback)();

class Button {
   private:
    int _pin;
    unsigned long _delay;
    unsigned long _lastDebounceTime;
    unsigned long _lastChangeTime;
    int _lastStateBtn;
    ButtonCallback _callBack = NULL;
    bool isTimeToUpdate();

   public:
    //Button(int pin, unsigned long delay, );
    void update();
    int state();
    void setCallback(ButtonCallback);
};

#endif  //Button_h