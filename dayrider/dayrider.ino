#include <Dagu4Motor.h>
#include <Encoder.h>
#include <Bridge.h>

#include "Movement.h"
#include <Adafruit_NeoPixel.h>
#include "NeoPixel.h"

Movement movement = Movement(5, 4, 3, 2, 11, 12, 9, 8);

// NeoPixel - KIT emulation :D
#define PIXEL_PIN 6
#define PIXEL_COUNT 8
#define KIT_LIGHT_DELAY 40 // in milliseconds

NeoPixel pixel = NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
int prevMillis = 0;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); // initializing 
  movement.begin();
  pixel.begin();
  pixel.reset();
  digitalWrite(13, HIGH); // ready to go
}

void loop() {
  unsigned long curMillis = millis();
  if (curMillis - prevMillis >= KIT_LIGHT_DELAY) {
    prevMillis = curMillis;
    pixel.kitLightNoTimer();
  }
  movement.poll_mailbox();

  delay(10);
}
