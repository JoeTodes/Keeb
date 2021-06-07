#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>
#include <Knob.h>

void openCalc() {
    Consumer.write(HID_CONSUMER_MENU);
    delay(50);
    Keyboard.print("calc");
    delay(100);
    Keyboard.write(KEY_ENTER);
}
Knob knobs[] = {
    Knob(0, 1, MEDIA_VOLUME_UP, MEDIA_VOLUME_DOWN),
    Knob(2, 3, openCalc, openCalc)};

void setup() {
    Consumer.begin();
}

void loop() {
    for (size_t i = 0; i < sizeof(knobs) / sizeof(knobs[0]); i++) {
        knobs[i].update();
    }

    delay(10);
}
