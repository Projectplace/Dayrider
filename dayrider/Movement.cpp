
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
     reset_ticks();
     right.setSpeed(0);
     left.setSpeed(0);
}

void Movement::go_forward(int spd) {
     if (current_direction == BACKWARD) {
        stop_movement();
        return;
     }
     if (current_direction == FORWARD) {
         left_motor(MOTOR_FORWARD, MOTOR_FAST_SPEED);
         right_motor(MOTOR_FORWARD, MOTOR_FAST_SPEED);
     } else {
         left_motor(MOTOR_FORWARD, spd);
         right_motor(MOTOR_FORWARD, spd);
     }
     current_direction = FORWARD;
     reset_ticks();
}

void Movement::go_backwards(int spd) {
     if (current_direction == FORWARD) {
        stop_movement();
        return;
     }
     left_motor(MOTOR_BACKWARDS, spd);
     right_motor(MOTOR_BACKWARDS, spd);
     current_direction = BACKWARD;
     reset_ticks();
}

void Movement::turn_left(int spd) {
     if (current_direction == RIGHT) {
        stop_movement();
        return;
     }
     if (current_direction == FORWARD) {
         left_motor(MOTOR_FORWARD, spd+10);
         right_motor(MOTOR_FORWARD, spd-10);
         current_direction = FORWARD_LEFT;
     } else {
         left_motor(MOTOR_FORWARD, spd);
         right_motor(MOTOR_BACKWARDS, 0);
         current_direction = LEFT;
     }     
     reset_ticks();
}

void Movement::turn_right(int spd) {
     if (current_direction == LEFT) {
        stop_movement();
        return;
     }
     if (current_direction == FORWARD) {
         right_motor(MOTOR_FORWARD, spd+10);
         left_motor(MOTOR_FORWARD, spd-10);
         current_direction = FORWARD_RIGHT;
     } else {
         right_motor(MOTOR_FORWARD, spd);
         left_motor(MOTOR_BACKWARDS, 0);
         current_direction = RIGHT;
     }
    reset_ticks();
}

void Movement::reset_ticks() {
     correction = 0;
     movement_count = 0;
     left.resetTicks();
     right.resetTicks();
}

int Movement::right_ticks() {
  return right.getTicks();
}

int Movement::left_ticks() {
  return left.getTicks();
}

//int count = 0;

void Movement::poll() {

  /*count ++;
  if (count == 10) {
    count = 0;
    Serial.print("Right ");
    Serial.print(right_ticks());
    Serial.print(" Left ");
    Serial.println(left_ticks());
    }*/

  if (current_direction == FORWARD) {
     if (correction == 0) {
        if (left_ticks() - right_ticks() > 10) {
           right_motor(MOTOR_FORWARD, MOTOR_SPEED+5);
           correction = LEFT;
        } else if (right_ticks() - left_ticks() > 10) {
           left_motor(MOTOR_FORWARD, MOTOR_SPEED+5);
           correction = RIGHT;
        }
     } else if (correction == LEFT) {
       if (left_ticks() - right_ticks() < 5) {
           right_motor(MOTOR_FORWARD, MOTOR_SPEED);
           correction = 0;
       }
     } else if (correction == RIGHT) {
       if (right_ticks() - left_ticks() < 5) {
           left_motor(MOTOR_FORWARD, MOTOR_SPEED);
           correction = 0;
       }
     }    
  }
  
  if (current_direction != 0) {
      movement_count = movement_count + 1;
      if ((movement_count == 20) && ((current_direction == RIGHT) || (current_direction == LEFT))) {
          stop_movement();
      }
      if ((movement_count == 20) && ((current_direction == FORWARD_LEFT) || (current_direction == FORWARD_RIGHT))) {
          go_forward(MOTOR_SPEED);
      }
      if ((movement_count == 500) && ((current_direction == FORWARD) || (current_direction == BACKWARD))) {
          stop_movement();
      }
  }
  return;
}
