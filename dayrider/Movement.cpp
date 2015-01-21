
#include "Movement.h"

#define MOTOR_FORWARD 1
#define MOTOR_BACKWARDS 0

#define MOTOR_SPEED 160
#define MOTOR_TURN_SPEED 80
#define MOTOR_FAST_SPEED 255

Movement::Movement(int right_pwm, int right_dir, int right_enca, int left_pwm, int left_dir, int left_enc) :
  right(right_pwm, right_dir, right_enca),
  left(left_pwm, left_dir, left_enc) {
  current_direction = 0;
  movement_count = 0; 
  backward_speed = 140;
  forward_speed = 160;
  turn_speed = 80;
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
  right.setSpeed(0);
  left.setSpeed(0);
}

void Movement::go_forward() {
  if (current_direction == BACKWARD) {
    stop_movement();
    return;
  } else if (current_direction == LEFT) {
    forward_left();
  } else if (current_direction == RIGHT) {
    forward_right();
  } else {
    left_motor(MOTOR_FORWARD, forward_speed);
    right_motor(MOTOR_FORWARD, forward_speed);
  }
  current_direction = FORWARD;
}

void Movement::stop_forward() {
  if (current_direction == FORWARD_LEFT) {
    turn_left();
  } else if (current_direction == FORWARD_RIGHT) {
    turn_right();
  } else {
    stop_movement();
  }
}

void Movement::go_backwards() {
  if (current_direction == FORWARD) {
    stop_movement();
    return;
  } else if (current_direction == LEFT) {
    backward_left();
  } else if (current_direction == RIGHT) {
    backward_right();
  } else {
    left_motor(MOTOR_BACKWARDS, backward_speed);
    right_motor(MOTOR_BACKWARDS, backward_speed);
    current_direction = BACKWARD;
}

void Movement::stop_backwards() {
  if (current_direction == BACKWARD_LEFT) {
    turn_left();
  } else if (current_direction == BACKWARD_RIGHT) {
    turn_right();
  } else {
    stop_movement();
  }
}

void Movement::forward_left() {
  left_motor(MOTOR_FORWARD, turn_speed+10);
  right_motor(MOTOR_FORWARD, turn_speed-10);
  current_direction = FORWARD_LEFT;
}

void Movement::forward_right() {
  left_motor(MOTOR_FORWARD, turn_speed-10);
  right_motor(MOTOR_FORWARD, turn_speed+10);
  current_direction = FORWARD_LEFT;
}

void Movement::backward_left() {
  left_motor(MOTOR_BACKWARD, turn_speed+10);
  right_motor(MOTOR_BACKWARD, turn_speed-10);
  current_direction = FORWARD_LEFT;
}

void Movement::backward_right() {
  left_motor(MOTOR_BACKWARD, turn_speed-10);
  right_motor(MOTOR_BACKWARD, turn_speed+10);
  current_direction = FORWARD_LEFT;
}

void Movement::turn_left() {
     if (current_direction == RIGHT) {
        stop_movement();
        return;
     } else if (current_direction == FORWARD) {
       forward_left();
     } else if (current_direction == BACKWARD) {
       forward_right();
     } else {
         left_motor(MOTOR_FORWARD, turn_speed);
         right_motor(MOTOR_BACKWARDS, 0);
         current_direction = LEFT;
     }     
}

void Movement::stop_left() {
  if (current_direction == BACKWARD_LEFT) {
    go_backwards();
  } else if (current_direction == FORWARD_LEFT) {
    go_forward();
  } else {
    stop_movement();
  }  
}

void Movement::turn_right() {
  if (current_direction == LEFT) {
    stop_movement();
    return;
  } else if (current_direction == FORWARD) {
    forward_right();
  } else if (current_direction == BACKWARD) {
    backward_right();
  } else {
    right_motor(MOTOR_FORWARD, turn_speed);
    left_motor(MOTOR_BACKWARDS, 0);
    current_direction = RIGHT;
  }
}

void Movement::stop_right() {
  if (current_direction == BACKWARD_RIGHT) {
    go_backwards();
  } else if (current_direction == FORWARD_RIGHT) {
    go_forward();
  } else {
    stop_movement();
  }  
}

int Movement::right_ticks() {
  return right.getTicks();
}

int Movement::left_ticks() {
  return left.getTicks();
}

void Movement::poll() {
  return;
}
