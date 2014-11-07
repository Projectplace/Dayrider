
#include "Movement.h"

#define MOTOR_FORWARD 1
#define MOTOR_BACKWARDS 0

#define MOTOR_SPEED 160
#define MOTOR_TURN_SPEED 80
#define MOTOR_FAST_SPEED 255

Movement::Movement(int right_pwm, int right_dir, int left_pwm, int left_dir) :
  right(right_pwm, right_dir, 0, 0, 0),
  left(left_pwm, left_dir, 0, 0, 0) {
  current_direction = 0;
  movement_count = 0; 
}

void Movement::begin() {
  left.begin();
  left.stopMotors();
  right.begin();
  right.stopMotors();
}

void Movement::left_motor(int dir, int spd) {
     left.setMotorDirection(!dir);
     left.setSpeed(spd);
}

void Movement::right_motor(int dir, int spd) {
     right.setMotorDirection(!dir);
     right.setSpeed(spd);
}

void Movement::stop_movement() {
     current_direction = 0;
     movement_count = 0;
     right.setSpeed(0);
     left.setSpeed(0);
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
     if (current_direction == FORWARD) {
         left_motor(MOTOR_FORWARD, MOTOR_SPEED+10);
         right_motor(MOTOR_FORWARD, MOTOR_SPEED-10);
         current_direction = FORWARD_LEFT;
     } else {
         left_motor(MOTOR_FORWARD, MOTOR_TURN_SPEED);
         right_motor(MOTOR_BACKWARDS, 0);
         current_direction = LEFT;
     }     
     movement_count = 0;
}

void Movement::turn_right() {
     if (current_direction == LEFT) {
        stop_movement();
        return;
     }
     if (current_direction == FORWARD) {
         right_motor(MOTOR_FORWARD, MOTOR_SPEED+10);
         left_motor(MOTOR_FORWARD, MOTOR_SPEED-10);
         current_direction = FORWARD_RIGHT;
     } else {
         right_motor(MOTOR_FORWARD, MOTOR_TURN_SPEED);
         left_motor(MOTOR_BACKWARDS, 0);
         current_direction = RIGHT;
     }
     movement_count = 0;
}

void Movement::poll() {
  if (current_direction != 0) {
      movement_count = movement_count + 1;
      if ((movement_count == 20) && ((current_direction == RIGHT) || (current_direction == LEFT))) {
          stop_movement();
      }
      if ((movement_count == 20) && ((current_direction == FORWARD_LEFT) || (current_direction == FORWARD_RIGHT))) {
          go_forward();
      }
      if ((movement_count == 500) && ((current_direction == FORWARD) || (current_direction == BACKWARD))) {
          stop_movement();
      }
  }
  return;
}
