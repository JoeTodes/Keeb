#include "Knob.h"

#include "Arduino.h"
#include "Encoder.h"
#include "HID-Project.h"

Knob::Knob(uint8_t pinA, uint8_t pinB) : _enc{pinA, pinB} {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
}

Knob::Knob(uint8_t pinA, uint8_t pinB, ConsumerKeycode upKey, ConsumerKeycode downKey) : _enc{pinA, pinB} {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    attachBehaviour(upKey, downKey);
}

void Knob::update() {
    long newPosition = _enc.read();
    int ticks = (newPosition - _oldPosition) / 4;

    for (int i = 0; i < abs(ticks); i++) {
        Consumer.write(ticks > 0 ? _incKey : _decKey);
        _oldPosition += ticks * 4;
    }
}

void Knob::attachUpBehaviour(ConsumerKeycode key) {
    _incKey = key;
}
void Knob::attachDownBehaviour(ConsumerKeycode key) {
    _decKey = key;
}
void Knob::attachBehaviour(ConsumerKeycode upKey, ConsumerKeycode downKey) {
    attachUpBehaviour(upKey);
    attachDownBehaviour(downKey);
}
