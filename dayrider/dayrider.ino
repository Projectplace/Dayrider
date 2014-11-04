#include <Bridge.h>
#include <Mailbox.h>

#include <Dagu4Motor.h>

                 // pwm, dir, cur(analog), encA, encB 
Dagu4Motor left_front(5, 4, 0, 0, 0);
Dagu4Motor left_back(3, 2, 0, 0, 0);
Dagu4Motor right_front(11, 12, 0, 0, 0);
Dagu4Motor right_back(9, 8, 0, 0, 0);

void setup() {
  //Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  Mailbox.begin();
  digitalWrite(13, HIGH);
    
  left_front.begin();
  left_front.stopMotors();
  left_back.begin();
  left_back.stopMotors();
  right_front.begin();
  right_front.stopMotors();
  right_back.begin();
  right_back.stopMotors();
  
}

void loop() {
  if (Mailbox.messageAvailable()) {
    process_cmd();
  }

  delay(10); 
}

#define LEFT 1
#define RIGHT 2
#define FORWARD 3
#define BACKWARD 4
#define FORWARD_LEFT 5
#define FORWARD_RIGHT 6

#define MOTOR_FORWARD 0
#define MOTOR_BACKWARDS 1

#define MOTOR_SPEED 100

int current_direction = 0;

void process_cmd() {
  String cmd;
  
  Mailbox.readMessage(cmd);
  if (cmd == "left") {
    turn_left();
  } else if (cmd == "right") {
    turn_right();
  } else if (cmd == "forward") {
    go_forward();
  } else if (cmd == "backward") {
    go_backwards();
  }

  //Serial.println(cmd);

}

void left_motor(int dir, int spd) {
     left_front.setMotorDirection(dir);
     left_front.setSpeed(spd);   
     left_back.setMotorDirection(!dir);
     left_back.setSpeed(spd);
}

void right_motor(int dir, int spd) {
     right_front.setMotorDirection(dir);
     right_front.setSpeed(spd);   
     right_back.setMotorDirection(!dir);
     right_back.setSpeed(spd);
}

void turn_left() {
     if (current_direction == RIGHT) {
        stop_movement();
        current_direction = 0;
        return;
     } else if (current_direction == FORWARD_RIGHT) {
        go_forward();
     }
     if (current_direction == FORWARD) {
        left_motor(MOTOR_FORWARD, MOTOR_SPEED + 70);
        right_motor(MOTOR_BACKWARDS, MOTOR_SPEED / 2);
        current_direction = FORWARD_LEFT;
     } else {
        left_motor(MOTOR_FORWARD, MOTOR_SPEED / 2);
        right_motor(MOTOR_BACKWARDS, MOTOR_SPEED / 2);
        current_direction = LEFT;
     }
}

void turn_right() {
     if (current_direction == LEFT) {
        stop_movement();
        current_direction = 0;
        return;
     } else if (current_direction == FORWARD_LEFT) {
        go_forward();
     }
     if (current_direction == FORWARD) {
        right_motor(MOTOR_FORWARD, MOTOR_SPEED + 70);
        left_motor(MOTOR_BACKWARDS, MOTOR_SPEED / 2);
        current_direction = FORWARD_RIGHT;
     } else {
        right_motor(MOTOR_FORWARD, MOTOR_SPEED / 2);
        left_motor(MOTOR_BACKWARDS, MOTOR_SPEED / 2);
        current_direction = RIGHT;
     }
}

void go_forward() {
     if (current_direction == BACKWARD) {
        stop_movement();
        current_direction = 0;
        return;
     }
     if (current_direction == FORWARD) {
         left_motor(MOTOR_FORWARD, MOTOR_SPEED + 100);
         right_motor(MOTOR_FORWARD, MOTOR_SPEED + 100);
     } else {
         left_motor(MOTOR_FORWARD, MOTOR_SPEED);
         right_motor(MOTOR_FORWARD, MOTOR_SPEED);
     }
     current_direction = FORWARD;
}

void go_backwards() {
     if (current_direction == FORWARD) {
        stop_movement();
        current_direction = 0;
        return;
     }
     left_motor(MOTOR_BACKWARDS, MOTOR_SPEED);
     right_motor(MOTOR_BACKWARDS, MOTOR_SPEED);
     current_direction = BACKWARD;
}

void stop_movement() {
     right_front.setSpeed(0);   
     right_back.setSpeed(0); 
     left_front.setSpeed(0); 
     left_back.setSpeed(0); 
}


