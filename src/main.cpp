#include <Arduino.h>
#include <Button.h>
#include <Encoder.h>
#include <HID-Project.h>
#include <Key.h>
#include <Knob.h>
#include <Matrix.h>
#include <Slider.h>
#include <vector>

// define macro functions like this
// Use Keyboard.press and Keyboard.release for individual keystrokes
// and Keyboard.print to type multiple characters at once.
// Delays are often needed to wait for windows and menus to open
void
openCalc()
{
  Keyboard.press(KEY_LEFT_WINDOWS);
  Keyboard.release(KEY_LEFT_WINDOWS);
  delay(700);
  Keyboard.print("calc");
  delay(100);
  Keyboard.press(KEY_ENTER);
  Keyboard.release(KEY_ENTER);
}

// Use this for buttons wired individually to Arduino pins
Button buttons[] = {
  // Button(6, KEY_0),
  // Button(7, KEY_1),
  // Button(5, KEY_UNDO),
  // Button(6, MEDIA_PLAY_PAUSE),
};

/*
Use this for buttons wired in a MATRIX
Assumes diodes go from switch to COLUMN lines
For example:
                       pin8                pin9
          _________      │    _______        │
         │OpenCal()│—►|——┤   │  "a"  │—►|————┤
          ---------      │    -------        │
pin5  ————————┴——————————│———————┘           │
                         │    _______        │
                         │   │  "5"  │—►|————┤
                         │    -------        │
pin5  ———————————————————│———————┘           │
          _________      │    _________      │
         │ Vol Up  │—►|——┘   │ VolDown │—►|——┘
          ---------           ---------
pin5  ————————┴——————————————————┘

Use an empty button ( Key() ) for gaps in rows
*/

// List all keys one row after another
std::vector<Key> keys = { Key(openCalc), Key(),      Key(MEDIA_VOLUME_UP),
                          Key(KEY_A),    Key(KEY_5), Key(MEDIA_VOLUME_DOWN) };
std::vector<int> rowPins = { 5, 6, 7 }; // in the same order as declared above
std::vector<int> colPins = { 8, 9 };    // in the same order as in the rows
Matrix matrix = Matrix(keys, colPins, rowPins);

// Encoders work best if using pins 0,1,2,3,4, or 7
// Middle pin goes to GND
Knob knobs[] = {
  // Knob(0, 1, MEDIA_VOLUME_UP, MEDIA_VOLUME_DOWN),
  // Knob(2, 3, openCalc, openCalc)
};

// For potentiometers and other analog inputs
// Allowed pins are 4,6,8,9,10,18,19,20,21
// Default behaviour is as volume control
Slider sliders[] = {
  Slider(10),
};

void
setup()
{
  matrix.setup();
  Consumer.begin();
}

void
loop()
{
  delay(10);
  matrix.update();
  for (size_t i = 0; i < sizeof(knobs) / sizeof(knobs[0]); i++) {
    knobs[i].update();
  }

  for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
    buttons[i].update();
  }

  for (size_t i = 0; i < sizeof(sliders) / sizeof(sliders[0]); i++) {
    sliders[i].update();
  }
}