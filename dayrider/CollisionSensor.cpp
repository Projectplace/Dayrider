#include "CollisionSensor.h"

#define SERVO_LEFT 150 
#define SERVO_CENTER 90
#define SERVO_RIGHT 20

CollisionSensor::CollisionSensor(int servoPin, int echoPin, int trigPin, int collisionDistance) {
  this->servoPin = servoPin;
  this->echoPin = echoPin;
  this->trigPin = trigPin;
  this->distance = collisionDistance;
  curServoPos = SERVO_CENTER;
}

void CollisionSensor::begin() {
  //servo.attach(servoPin);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  //servo.write(SERVO_CENTER);
}

bool CollisionSensor::collisionDetected() {
  //servoSweep(); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long d = pulseIn(echoPin, HIGH);

  if ((d / 58) <= distance) {
    if (curServoPos == SERVO_LEFT) {
      collisionDirection = -1;
    } else if (curServoPos == SERVO_CENTER) {
      collisionDirection = 0;
    } else {
      collisionDirection = 1;
    }
    return true;
  }
  return false;
}

int CollisionSensor::collisionDetails() {
  return collisionDirection;
}

/*
void CollisionSensor::servoSweep() {
  if (servoDirection) { // right -> left 
    if (curServoPos == SERVO_RIGHT) {
      servo.write(SERVO_CENTER);
      curServoPos = SERVO_CENTER;
    } else if (curServoPos == SERVO_CENTER) {
      servo.write(SERVO_LEFT);
      curServoPos = SERVO_LEFT;
      servoDirection = false;
    }
  } else {
    if (curServoPos == SERVO_LEFT) {
      servo.write(SERVO_CENTER);
      curServoPos = SERVO_CENTER;
    } else if (curServoPos == SERVO_CENTER) {
      servo.write(SERVO_RIGHT);
      curServoPos = SERVO_RIGHT;
      servoDirection = true;
    }
  }
}
*/
