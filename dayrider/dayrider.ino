#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <WiFi.h>

#include "Motor.h"
#include "Movement.h"
#include "NeoPixel.h"
//#include "CollisionSensor.h"

Movement movement = Movement(11, 12, 2, 5, 4, 3);

// NeoPixel - KIT emulation :D
#define PIXEL_PIN 6
#define PIXEL_COUNT 8

// Collision sensor
#define SERVO_PIN A0 // Analog 0
#define ECHO_PIN 10
#define TRIG_PIN 7
#define COLLISION_DISTANCE 50 // in centimeters

NeoPixel pixel = NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

Controller controller = Controller(&movement, &pixel);

//CollisionSensor s1 = CollisionSensor(SERVO_PIN, ECHO_PIN, TRIG_PIN, COLLISION_DISTANCE);

void setup() {
  pinMode(13, OUTPUT);
  //Serial.begin(9600);
  digitalWrite(13, LOW); // initializing
  //Bridge.begin();
  //Mailbox.begin();
  movement.begin();
  pixel.begin();
  pixel.reset();
  controller.begin();
  //s1.begin();
  digitalWrite(13, HIGH); // ready to go
}

void loop() {

  //poll_mailbox();

  //if (s1.collisionDetected() && movement.current_direction == FORWARD ) {
  //  movement.stop_movement();
  //}
  controller.poll();

  movement.poll();

  pixel.poll();

  controller.auto_control_headlight();

  delay(10);
}
