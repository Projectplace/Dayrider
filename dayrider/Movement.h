
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
#define BACKWARD_LEFT 7
#define BACKWARD_RIGHT 8

class Movement {  
  Motor right;
  Motor left;
  void left_motor(int dir, int spd);
  void right_motor(int dir, int spd);
  int left_ticks();
  int right_ticks();

  void forward_left();
  void forward_right();
  void backward_left();
  void backward_right();

public:  
  Movement(int right_pwm, int right_dir, int right_enc, int left_pwm, int left_dir, int left_enca);
  void stop_movement();
  void begin();
  void poll();
  void go_forward();
  void stop_forward();
  void go_backwards();
  void stop_backwards();
  void turn_left();
  void stop_left();
  void turn_right();
  void stop_right();

  int turn_speed;
  int forward_speed;
  int backward_speed;

  int current_direction;
};

#endif
