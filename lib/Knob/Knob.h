#ifndef Knob_h
#define Knob_h

#include "Arduino.h"
#include "Encoder.h"
#include "HID-Project.h"

typedef void (*KnobCallback)();

class Knob {
   private:
    ConsumerKeycode _incKey = MEDIA_VOLUME_UP;
    ConsumerKeycode _decKey = MEDIA_VOLUME_DOWN;

    int _oldPosition = 0;
    Encoder _enc;
    KnobCallback _incCallback = NULL;
    KnobCallback _decCallback = NULL;

   public:
    Knob(uint8_t pinA, uint8_t pinB);
    Knob(uint8_t pinA, uint8_t pinB, ConsumerKeycode upKey, ConsumerKeycode downKey);
    Knob(uint8_t pinA, uint8_t pinB, KnobCallback upCallback, KnobCallback downCallback);

    void update();
    void attachUpBehaviour(ConsumerKeycode key);
    void attachDownBehaviour(ConsumerKeycode key);
    void attachBehaviour(ConsumerKeycode upKey, ConsumerKeycode downKey);
};

#endif  // Knob_h
