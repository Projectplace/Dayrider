#ifndef Controller_h
#define Controller_h

#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>

#include "Movement.h"
#include "NeoPixel.h"

#define HEADLIGHT_MODE_AUTO 0
#define HEADLIGHT_MODE_KITMODE 1
#define HEADLIGHT_MODE_CARLIGHT 2
#define HEADLIGHT_MODE_OFF 3

class Controller {  
  WiFiServer server;
  WiFiClient client;
  Movement *movement;
  NeoPixel *pixel;
  String currentline;

  unsigned long previous_command_millis;
  unsigned long was_running_millis;
  int headlight_mode;
  int headlight_auto_state;

public:  
  Controller(Movement *movement, NeoPixel *pixel);
  void begin();
  int poll();

  void auto_control_headlight();
};

#endif
