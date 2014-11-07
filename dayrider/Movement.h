
#ifndef Movement_h
#define Movement_h

#include "Arduino.h"
#include <Dagu4Motor.h>

#define LEFT 1
#define RIGHT 2
#define FORWARD 3
#define BACKWARD 4

class Movement {  
  Dagu4Motor right_front;
  Dagu4Motor right_back;
  Dagu4Motor left_front;
  Dagu4Motor left_back;
  void left_motor(int dir, int spd);
  void right_motor(int dir, int spd);
  int movement_count;

public:  
  Movement(int rf_pwm, int rf_dir, int rb_pwm, int rb_dir, int lf_pwm, int lf_dir, int lb_pwm, int lb_dir);
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
