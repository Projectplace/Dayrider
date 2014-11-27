
#include "Motor.h"

// Yun has 5 interrupts
#define CORE_NUM_INTERRUPT    5
#define CORE_INT0_PIN         3
#define CORE_INT1_PIN         2
#define CORE_INT2_PIN         0
#define CORE_INT3_PIN         1
#define CORE_INT4_PIN         7

static uint32_t* INTERRUPT_TICKS[CORE_NUM_INTERRUPT];
                           
void int0fun() { uint32_t *tick = INTERRUPT_TICKS[0]; tick[0]++; }
void int1fun() { uint32_t *tick = INTERRUPT_TICKS[1]; tick[0]++; }
void int2fun() { uint32_t *tick = INTERRUPT_TICKS[2]; tick[0]++; }
void int3fun() { uint32_t *tick = INTERRUPT_TICKS[3]; tick[0]++; }
void int4fun() { uint32_t *tick = INTERRUPT_TICKS[4]; tick[0]++; }

Motor::Motor(int pwm_pin, int dir_pin, int enc_pin) {
  this->pwm_pin = pwm_pin;
  this->dir_pin = dir_pin;
  this->enc_pin = enc_pin;
}

void Motor::begin() {
  pinMode(pwm_pin, OUTPUT);  
  pinMode(dir_pin, OUTPUT);
  if (enc_pin == CORE_INT0_PIN) {
    attachInterrupt(0, int0fun, CHANGE);
    INTERRUPT_TICKS[0] = &ticks;
  } else if (enc_pin == CORE_INT1_PIN) {
    attachInterrupt(1, int1fun, CHANGE);
    INTERRUPT_TICKS[1] = &ticks;
  } else if (enc_pin == CORE_INT2_PIN) {
    attachInterrupt(2, int2fun, CHANGE);
    INTERRUPT_TICKS[2] = &ticks;
  } else if (enc_pin == CORE_INT3_PIN) {
    attachInterrupt(3, int3fun, CHANGE);
    INTERRUPT_TICKS[3] = &ticks;
  } else if (enc_pin == CORE_INT4_PIN) {
    attachInterrupt(4, int4fun, CHANGE);
    INTERRUPT_TICKS[4] = &ticks;
  } 
}

void Motor::setMotorDirection(int dir) {
  if (dir == 1) {  
    digitalWrite(dir_pin, LOW);
  } else {  
    digitalWrite(dir_pin, HIGH);
  } 
}

void Motor::setSpeed(int spd) {
  spd = constrain(spd, 0, 255);
  analogWrite(pwm_pin, spd);
}

void Motor::stopMotors() {
  setSpeed(0);
}

void Motor::resetTicks() {
  ticks = 0;
}

int Motor::getTicks() {
  return ticks;
}

