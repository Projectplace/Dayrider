#include "Arduino.h"
//#include <Servo.h>

#ifndef CollisionSensor_h
#define CollisionSensor_h

class CollisionSensor {
  public:
    CollisionSensor(int servoPin, int echoPin, int trigPin, int collisionDistance);
    void begin();
    bool collisionDetected();
    int collisionDetails();

  private:
    int echoPin;
    int trigPin;
    int servoPin;
    int distance;
    int collisionDirection;
    int curServoPos;
    bool servoDirection; // 0 = left -> right, 1 = right -> left
    //void servoSweep();
    //Servo servo;
};

#endif
