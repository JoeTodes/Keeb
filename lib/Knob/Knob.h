#ifndef Knob_h
#define Knob_h

#include "Arduino.h"
#include "Encoder.h"
#include "HID-Project.h"

class Knob {
   private:
    ConsumerKeycode _incKey = MEDIA_VOLUME_UP;
    ConsumerKeycode _decKey = MEDIA_VOLUME_DOWN;

   public:
    Knob(int pinA, int pinB);
    void update();
};

#endif  // Knob_h
