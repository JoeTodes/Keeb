#include "Knob.h"

#include "Arduino.h"
#include "Encoder.h"
#include "HID-Project.h"

Knob::Knob(uint8_t pinA, uint8_t pinB) : _enc{pinA, pinB} {
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
}

Knob::Knob(uint8_t pinA, uint8_t pinB, ConsumerKeycode upKey, ConsumerKeycode downKey) : _enc{pinA, pinB} {
    _mode = MEDIAKEY;
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    _incConsumerKey = upKey;
    _decConsumerKey = downKey;
}
Knob::Knob(uint8_t pinA, uint8_t pinB, KeyboardKeycode upKey, KeyboardKeycode downKey) : _enc{pinA, pinB} {
    _mode = KEYBOARDKEY;
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
    _incKey = upKey;
    _decKey = downKey;
}
Knob::Knob(uint8_t pinA, uint8_t pinB, KnobCallback upCallback, KnobCallback downCallback) : _enc{pinA, pinB} {
    _mode = MACRO;
    _incCallback = upCallback;
    _decCallback = downCallback;
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);
}

void Knob::update() {
    long newPosition = _enc.read();
    int ticks = (newPosition - _oldPosition) / 4;

    for (int i = 0; i < abs(ticks); i++) {
        switch (_mode) {
            case MEDIAKEY:
                Consumer.write(ticks > 0 ? _incConsumerKey : _decConsumerKey);
                break;
            case KEYBOARDKEY:
                Keyboard.write(ticks > 0 ? _incKey : _decKey);
            case MACRO:
                ticks > 0 ? this->_incCallback() : this->_decCallback();
            default:
                break;
        }

        _oldPosition += ticks * 4;
    }
}

void Knob::attachUpBehaviour(ConsumerKeycode key) {
    _mode = MEDIAKEY;
    _incConsumerKey = key;
}
void Knob::attachDownBehaviour(ConsumerKeycode key) {
    _mode = MEDIAKEY;
    _decConsumerKey = key;
}
void Knob::attachUpBehaviour(KeyboardKeycode key) {
    _mode = KEYBOARDKEY;
    _incKey = key;
}
void Knob::attachDownBehaviour(KeyboardKeycode key) {
    _mode = KEYBOARDKEY;
    _decKey = key;
}
void Knob::attachUpBehaviour(KnobCallback callback) {
    _mode = MACRO;
    _incCallback = callback;
}
void Knob::attachDownBehaviour(KnobCallback callback) {
    _mode = MACRO;
    _decCallback = callback;
}
