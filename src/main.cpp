#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>
#include <Knob.h>

Knob knob(2, 3);

void setup() {
    Consumer.begin();
    Serial.begin(9600);
}

void loop() {
    knob.update();

    delay(10);
}