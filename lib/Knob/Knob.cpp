#include "Arduino.h"
#include "Encoder.h"
#include "HID-Project.h"
#include "Knob.h"

Knob::Knob(uint8_t pinA, uint8_t pinB) : _enc{pinA, pinB}
{
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
}

void Knob::update(){
    long newPosition = _enc.read();
    int ticks = (newPosition - _oldPosition) / 4;

    for (int i = 0; i < abs(ticks); i++) {
        Consumer.write(ticks > 0 ? _incKey : _decKey);
        _oldPosition += ticks * 4;
    }
}
