
#include "Movement.h"

#define MOTOR_FORWARD 1
#define MOTOR_BACKWARDS 0

#define MOTOR_SPEED 120
#define MOTOR_TURN_SPEED 100
#define MOTOR_FAST_SPEED 255

Movement::Movement(int rf_pwm, int rf_dir, int rb_pwm, int rb_dir, int lf_pwm, int lf_dir, int lb_pwm, int lb_dir) :
  right_front(rf_pwm, rf_dir, 0, 0, 0),
  right_back(rb_pwm, rb_dir, 0, 0, 0),
  left_front(lf_pwm, lf_dir, 0, 0, 0),
  left_back(lb_pwm, lb_dir, 0, 0, 0) {
  current_direction = 0;
  movement_count = 0; 
}

void Movement::begin() {
  left_front.begin();
  left_front.stopMotors();
  left_back.begin();
  left_back.stopMotors();
  right_front.begin();
  right_front.stopMotors();
  right_back.begin();
  right_back.stopMotors();
}

void Movement::left_motor(int dir, int spd) {
     left_front.setMotorDirection(dir);
     left_front.setSpeed(spd);
     left_back.setMotorDirection(!dir);
     left_back.setSpeed(spd);
}

void Movement::right_motor(int dir, int spd) {
     right_front.setMotorDirection(dir);
     right_front.setSpeed(spd);
     right_back.setMotorDirection(!dir);
     right_back.setSpeed(spd);
}

void Movement::stop_movement() {
     current_direction = 0;
     movement_count = 0;
     right_front.setSpeed(0);
     right_back.setSpeed(0);
     left_front.setSpeed(0);
     left_back.setSpeed(0);
}

void Movement::go_forward() {
     if (current_direction == BACKWARD) {
        stop_movement();
        return;
     }
     if (current_direction == FORWARD) {
         left_motor(MOTOR_FORWARD, MOTOR_FAST_SPEED);
         right_motor(MOTOR_FORWARD, MOTOR_FAST_SPEED);
     } else {
         left_motor(MOTOR_FORWARD, MOTOR_SPEED);
         right_motor(MOTOR_FORWARD, MOTOR_SPEED);
     }
     current_direction = FORWARD;
     movement_count = 0;
}

void Movement::go_backwards() {
     if (current_direction == FORWARD) {
        stop_movement();
        return;
     }
     left_motor(MOTOR_BACKWARDS, MOTOR_SPEED);
     right_motor(MOTOR_BACKWARDS, MOTOR_SPEED);
     current_direction = BACKWARD;
     movement_count = 0;
}

void Movement::turn_left() {
     if (current_direction == RIGHT) {
        stop_movement();
        return;
     }
     left_motor(MOTOR_FORWARD, MOTOR_TURN_SPEED);
     right_motor(MOTOR_BACKWARDS, MOTOR_TURN_SPEED);
     current_direction = LEFT;
     movement_count = 0;
}

void Movement::turn_right() {
     if (current_direction == LEFT) {
        stop_movement();
        return;
     }
     right_motor(MOTOR_FORWARD, MOTOR_TURN_SPEED);
     left_motor(MOTOR_BACKWARDS, MOTOR_TURN_SPEED);
     current_direction = RIGHT;
     movement_count = 0;
}

void Movement::poll() {
  if (current_direction != 0) {
      movement_count = movement_count + 1;
      if ((movement_count == 50) && ((current_direction == RIGHT) || (current_direction == LEFT))) {
          stop_movement();
      }
      if ((movement_count == 500) && ((current_direction == FORWARD) || (current_direction == BACKWARD))) {
          stop_movement();
      }
  }
  return;
}
