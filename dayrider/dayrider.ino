#include <Bridge.h>
#include <Mailbox.h>

#include <Dagu4Motor.h>

//YunServer server;
              // pwn, dir, cur(analog), encA, encB 
Dagu4Motor left(11, 12, 0, 0, 0);
Dagu4Motor right(3, 2, 0, 0, 0);

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  Mailbox.begin();
  digitalWrite(13, HIGH);
  
  Serial.println("Starting Dayrider 0.1");
  
  left.begin();
  left.stopMotors();
  
}

void loop() {
  if (Mailbox.messageAvailable()) {
    process_mb();
  }

  delay(50); 
}

void process_mb() {
  int start, end, dir, spd;
  String msg, side, tmp;
  
  Mailbox.readMessage(msg);

  Serial.println(msg);

  end = msg.indexOf('/');
  side = msg.substring(0, end);
  start = end+1;
  end = msg.indexOf('/', start);
  dir = msg.substring(start, end).toInt();
  start = end+1;
  spd = msg.substring(start).toInt();

  motorCommand(side, dir, spd);  
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


