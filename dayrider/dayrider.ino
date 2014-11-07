#include <Dagu4Motor.h>
#include <Encoder.h>
#include <Bridge.h>
#include <Mailbox.h>

#include "Movement.h"
#include <Adafruit_NeoPixel.h>
#include "NeoPixel.h"
#include "CollisionSensor.h"

Movement movement = Movement(5, 4, 3, 2, 11, 12, 9, 8);

// NeoPixel - KIT emulation :D
#define PIXEL_PIN 6
#define PIXEL_COUNT 8
#define HEADLIGHT_MODE_AUTO 0
#define HEADLIGHT_MODE_KITMODE 1
#define HEADLIGHT_MODE_CARLIGHT 2
#define HEADLIGHT_MODE_OFF 3

// Collision sensor
#define SERVO_PIN A0 // Analog 0
#define ECHO_PIN 10
#define TRIG_PIN 7
#define COLLISION_DISTANCE 50 // in centimeters

NeoPixel pixel = NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

CollisionSensor s1 = CollisionSensor(SERVO_PIN, ECHO_PIN, TRIG_PIN, COLLISION_DISTANCE);

unsigned long previous_command_millis = 0;
unsigned long was_running_millis = 0;
int headlight_mode = HEADLIGHT_MODE_AUTO;
int headlight_auto_state = HEADLIGHT_MODE_OFF;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW); // initializing
  Bridge.begin();
  Mailbox.begin();
  movement.begin();
  pixel.begin();
  pixel.reset();
  digitalWrite(13, HIGH); // ready to go
}

void poll_mailbox() {
  String cmd;

  if (!Mailbox.messageAvailable()) {
      return;
  }

  previous_command_millis = millis();

  Mailbox.readMessage(cmd);
  if (cmd == "left") {
    movement.turn_left();
  } else if (cmd == "right") {
    movement.turn_right();
  } else if (cmd == "forward") {
    movement.go_forward();
  } else if (cmd == "backward") {
    movement.go_backwards();
  } else if (cmd == "headlight/kitmode") {
    pixel.toggleKitLight(true);
    headlight_mode = HEADLIGHT_MODE_KITMODE;
  } else if (cmd == "headlight/carlight") {
    pixel.toggleHeadLights(true);
    headlight_mode = HEADLIGHT_MODE_CARLIGHT;
  } else if (cmd == "headlight/off") {
    pixel.toggleKitLight(false);
    headlight_mode = HEADLIGHT_MODE_OFF;
  } else if (cmd == "headlight/auto") {
    headlight_mode = HEADLIGHT_MODE_AUTO;
    pixel.toggleKitLight(false);
  }
}

void auto_control_headlight() {
  if (headlight_mode != HEADLIGHT_MODE_AUTO) {
    return;
  }
  unsigned long current_millis = millis();

  if (was_running_millis > current_millis) {
      // timer wrapped
      was_running_millis = 0;
  }

  if (movement.current_direction != 0) {
    // while moving, use headlights
    if (headlight_auto_state != HEADLIGHT_MODE_CARLIGHT) {
      pixel.toggleHeadLights(true);
      headlight_auto_state = HEADLIGHT_MODE_CARLIGHT;
    }
    was_running_millis = current_millis;
  } else {
    if (current_millis - was_running_millis >= 10200) {
      // sleep after 10 sec
      if (headlight_auto_state != HEADLIGHT_MODE_OFF) {
        pixel.toggleKitLight(false);      
        headlight_auto_state = HEADLIGHT_MODE_OFF;
      }
    } else if (current_millis - was_running_millis >= 1000) {
      // after 1 sec, show kit lights
      if (headlight_auto_state != HEADLIGHT_MODE_KITMODE) {
        pixel.toggleKitLight(true);
        headlight_auto_state = HEADLIGHT_MODE_KITMODE;
      }
    }
  }
}

void loop() {

  poll_mailbox();

  if (s1.collisionDetected()) {
    movement.stop_movement();
  }
  movement.poll();

  pixel.poll();

  auto_control_headlight();

  delay(10);
}
