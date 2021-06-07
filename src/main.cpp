#include <Arduino.h>
#include <Button.h>
#include <Encoder.h>
#include <HID-Project.h>
#include <Knob.h>

void
openCalc()
{
  Keyboard.press(KEY_LEFT_WINDOWS);
  Keyboard.release(KEY_LEFT_WINDOWS);
  delay(1000);
  Keyboard.print("calc");
  delay(100);
  Keyboard.press(KEY_ENTER);
  Keyboard.release(KEY_ENTER);
}

// Use this for buttons wired individually to Arduino pins
Button buttons[] = {
  // Button(4, openCalc),
  // Button(5, KEY_UNDO),
  // Button(6, MEDIA_PLAY_PAUSE),
};

// Use this for buttons wired in a MATRIX
// Assumes diodes go from switch to COLUMN lines
// Use an empty button ( Button() ) for gaps in rows
Button row1[] = { Button(openCalc), Button(KEY_A), Button() };
Button row2[] = { Button(KEY_0), Button(), Button(MEDIA_PLAY_PAUSE) };
Button* rows[] = { row1, row2 };
int colCount = sizeof(rows[0]) / sizeof(rows[0][0]);
int rowCount = sizeof(rows) / sizeof(rows[0]);
int rowPins[] = { 7, 8 };      // in the same order as declared above
int colPins[] = { 9, 10, 11 }; // in the same order as in the rows
/*
    ie. pin 9 connects to the diodes from the buttons for openCalc and KEY_0,
    pin 11 connects to the diode from the Play/Pause button
*/

Knob knobs[] = {
  // Knob(0, 1, MEDIA_VOLUME_UP, MEDIA_VOLUME_DOWN),
  // Knob(2, 3, openCalc, openCalc)
};

void
setup()
{
  Serial.begin(9600);
  for (int i = 0; i < rowCount; i++) {
    pinMode(rowPins[i], INPUT);
  }
  for (int i = 0; i < colCount; i++) {
    pinMode(colPins[i], INPUT);
  }

  Consumer.begin();
}

void
loop()
{
  for (size_t i = 0; i < sizeof(knobs) / sizeof(knobs[0]); i++) {
    knobs[i].update();
  }

  for (size_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++) {
    buttons[i].update();
  }

  for (int c = 0; c < colCount; c++) {
    int colPin = colPins[c];
    pinMode(colPin, OUTPUT);
    digitalWrite(colPin, LOW);

    for (int r = 0; r < rowCount; r++) {
      Button b = rows[r][c];
      if (b.getMode() != BUTTON_NULL) {
        int rowPin = rowPins[r];
        pinMode(rowPin, INPUT_PULLUP);
        b.update();
        pinMode(rowPin, INPUT);
      }
    }
    pinMode(colPin, INPUT);
  }
}