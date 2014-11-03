#include <Bridge.h>
#include <Mailbox.h>

#include <Dagu4Motor.h>

//YunServer server;
              // pwn, dir, cur(analog), encA, encB 
Dagu4Motor left(11, 12, 0, 0, 0);
Dagu4Motor right(3, 2, 0, 0, 0);

void setup() {
  //Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  Mailbox.begin();
  digitalWrite(13, HIGH);
  
  //Serial.println("Starting Dayrider 0.1");
  
  left.begin();
  left.stopMotors();
  
}

void loop() {
  if (Mailbox.messageAvailable()) {
    process_cmd();
  }

  delay(50); 
}

#define LEFT 1
#define RIGHT 2
#define FORWARD 3
#define BACKWARD 4

#define MOTOR_FORWARD 0
#define MOTOR_BACKWARD 1

#define MOTOR_SPEED 150

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

void turn_left() {
     if (current_direction == RIGHT) {
        stop_movement();
        current_direction = 0;
        return;
     }  
     left.setMotorDirection(MOTOR_FORWARD);
     left.setSpeed(MOTOR_SPEED);   
     //right.setMotorDirection(MOTOR_BACKWARD);
     //right.setSpeed(MOTOR_SPEED / 2);
     current_direction = LEFT;
}

void turn_right() {
     if (current_direction == LEFT) {
        stop_movement();
        current_direction = 0;
        return;
     }
     //right.setMotorDirection(MOTOR_FORWARD);
     //right.setSpeed(MOTOR_SPEED);   
     left.setMotorDirection(MOTOR_BACKWARD);
     left.setSpeed(MOTOR_SPEED / 2);   
     current_direction = RIGHT;
}

void go_forward() {
     if (current_direction == BACKWARD) {
        stop_movement();
        current_direction = 0;
        return;
     }
     //right.setMotorDirection(MOTOR_FORWARD);
     //right.setSpeed(MOTOR_SPEED);   
     left.setMotorDirection(MOTOR_FORWARD);
     left.setSpeed(MOTOR_SPEED);   
     current_direction = FORWARD;
}

void go_backwards() {
     if (current_direction == FORWARD) {
        stop_movement();
        current_direction = 0;
        return;
     }
     //right.setMotorDirection(MOTOR_BACKWARD);
     //right.setSpeed(MOTOR_SPEED);   
     left.setMotorDirection(MOTOR_BACKWARD);
     left.setSpeed(MOTOR_SPEED);   
     current_direction = BACKWARD;
}

void stop_movement() {
     //right.setSpeed(0);   
     left.setSpeed(0); 
}

void motorCommand(String side, int dir, int spd) {
  
  if (side == "left") {
     left.setMotorDirection(dir);
     left.setSpeed(spd);
  } else if (side == "right") {
     right.setMotorDirection(dir);
     right.setSpeed(spd); 
  } else if (side == "both") {
     left.setMotorDirection(dir);
     left.setSpeed(spd); 
     right.setMotorDirection(dir);
     right.setSpeed(spd); 
  }
}


