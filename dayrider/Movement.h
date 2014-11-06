
#ifndef Movement_h
#define Movement_h

#include "Arduino.h"
#include <Mailbox.h>
#include <Dagu4Motor.h>

class Movement {  
public:  
  Movement(int rf_pwm, int rf_dir, int rb_pwm, int rb_dir, int lf_pwm, int lf_dir, int lb_pwm, int lb_dir);
  void begin();
  void poll_mailbox();

 private:    
  Dagu4Motor right_front;
  Dagu4Motor right_back;
  Dagu4Motor left_front;
  Dagu4Motor left_back;
  void left_motor(int dir, int spd);
  void right_motor(int dir, int spd);
  void stop_movement();
  void go_forward();
  void go_backwards();
  void turn_left();
  void turn_right();

  int current_direction;
  int movement_count;

};

#endif