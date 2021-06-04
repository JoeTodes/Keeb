#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>
#include <Knob.h>

Encoder myEnc(2, 3);
long oldPosition = 0;

void setup() {
    Consumer.begin();
    Serial.begin(9600);
}

void loop() {
    long newPosition = myEnc.read();
    int ticks = (newPosition - oldPosition) / 4;

    for (int i = 0; i < abs(ticks); i++) {
        Consumer.write(ticks > 0 ? MEDIA_VOLUME_UP : MEDIA_VOLUME_DOWN);
        oldPosition += ticks * 4;
    }

    delay(10);
}