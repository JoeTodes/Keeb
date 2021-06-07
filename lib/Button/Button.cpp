#include "Button.h"

#include "Arduino.h"
#include "HID-Project.h"

Button::Button()
{
  _mode = BUTTON_NULL;
}

Button::Button(int pin, KeyboardKeycode key)
{
  pinMode(pin, INPUT_PULLUP);
  _mode = BUTTON_KEYBOARDKEY;
  _key = key;
  _pin = pin;
}
Button::Button(int pin, ConsumerKeycode key)
{
  pinMode(pin, INPUT_PULLUP);
  _mode = BUTTON_MEDIAKEY;
  _consumerKey = key;
  _pin = pin;
}
Button::Button(int pin, ButtonCallback macro)
{
  pinMode(pin, INPUT_PULLUP);
  _mode = BUTTON_MACRO;
  _callback = macro;
  _pin = pin;
}
Button::Button(KeyboardKeycode key)
{
  _mode = BUTTON_KEYBOARDKEY;
  _key = key;
}
Button::Button(ConsumerKeycode key)
{
  _mode = BUTTON_MEDIAKEY;
  _consumerKey = key;
}
Button::Button(ButtonCallback macro)
{
  _mode = BUTTON_MACRO;
  _callback = macro;
}

void
Button::update(int pin)
{
  int btnState = digitalRead(pin);
  if (btnState == _lastStateBtn) {
    _lastChangeTime = millis();
  } else if (millis() - _lastChangeTime > _delay) {
    _lastStateBtn = btnState;
    _lastChangeTime = millis();

    if (_lastStateBtn == LOW) {
      switch (_mode) {
        case BUTTON_MEDIAKEY:
          Consumer.write(_consumerKey);
          break;
        case BUTTON_KEYBOARDKEY:
          Keyboard.write(_key);
          break;
        case BUTTON_MACRO:
          this->_callback();
          break;
        default:
          break;
      }
    }
  }
}

void
Button::update()
{
  this->update(_pin);
}

int
Button::state()
{
  return _lastStateBtn;
}

ButtonMode
Button::getMode()
{
  return _mode;
}
