
#ifndef Movement_h
#define Movement_h

#include "Arduino.h"
#include <Dagu4Motor.h>

#define LEFT 1
#define RIGHT 2
#define FORWARD 3
#define BACKWARD 4
#define FORWARD_LEFT 5
#define FORWARD_RIGHT 6

class Movement {  
  Dagu4Motor right;
  Dagu4Motor left;
  void left_motor(int dir, int spd);
  void right_motor(int dir, int spd);
  int movement_count;

public:  
  Movement(int right_pwm, int right_dir, int left_pwm, int left_dir);
  void stop_movement();
  void begin();
  void poll();
  void go_forward();
  void go_backwards();
  void turn_left();
  void turn_right();

  int current_direction;
};

#endif
