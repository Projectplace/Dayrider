
#ifndef TwoMotors_h
#define TwoMotors_h

#include "Arduino.h"

class Motor {  
  int pwm_pin;
  int dir_pin;
  int enc_pin;
  uint32_t ticks;

public:  
  Motor(int pwm_pin, int dir_pin, int enc_pin);
  void begin();
  void setMotorDirection(int spd);
  void setSpeed(int spd);
  int getTicks();
  void resetTicks();
  void stopMotors();
};

#endif
