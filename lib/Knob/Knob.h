#ifndef Knob_h
#define Knob_h

#include "Arduino.h"
#include "Encoder.h"
#include "HID-Project.h"

class Knob {
   private:
    ConsumerKeycode _incKey = MEDIA_VOLUME_UP;
    ConsumerKeycode _decKey = MEDIA_VOLUME_DOWN;
   
    int _oldPosition = 0;
    Encoder _enc;

   public:
    Knob(uint8_t pinA, uint8_t pinB);
    void update();
};

#endif  // Knob_h
