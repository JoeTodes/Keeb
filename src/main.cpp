#include <Arduino.h>
#include <Encoder.h>
#include <HID-Project.h>
#include <Knob.h>

Knob knobs[1] = {
    Knob(0, 1, MEDIA_VOLUME_UP, MEDIA_VOLUME_DOWN),
    //,Knob(2, 3, CONSUMER_BRIGHTNESS_UP, CONSUMER_BRIGHTNESS_DOWN)
};

void setup() {
    Consumer.begin();
}

void loop() {
    for (size_t i = 0; i < sizeof(knobs) / sizeof(knobs[0]); i++) {
        knobs[i].update();
    }

    delay(10);
}