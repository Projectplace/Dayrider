#include <Dagu4Motor.h>
#include <Encoder.h>
#include <Bridge.h>

#include "Movement.h"

Movement movement = Movement(5, 4, 3, 2, 11, 12, 9, 8);

void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW); // initializing 
  movement.begin();
  digitalWrite(13, HIGH); // ready to go
}

void loop() {

  movement.poll_mailbox();

  delay(10);
}
