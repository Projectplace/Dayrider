
#ifndef Movement_h
#define Movement_h

#include "Arduino.h"
#include "Motor.h"

#define LEFT 1
#define RIGHT 2
#define FORWARD 3
#define BACKWARD 4
#define FORWARD_LEFT 5
#define FORWARD_RIGHT 6

class Movement {  
  Motor right;
  Motor left;
  void left_motor(int dir, int spd);
  void right_motor(int dir, int spd);
  int movement_count;
  int correction;
  int left_ticks();
  int right_ticks();
  void reset_ticks();

public:  
  Movement(int right_pwm, int right_dir, int right_enc, int left_pwm, int left_dir, int left_enca);
  void stop_movement();
  void begin();
  void poll();
  void go_forward(int spd);
  void go_backwards(int spd);
  void turn_left(int spd);
  void turn_right(int spd);

  int current_direction;
};

#endif
