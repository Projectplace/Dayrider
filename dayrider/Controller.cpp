

#include "Controller.h"

Controller::Controller(Movement *movement, NeoPixel * pixel) : server(80) {
  client = NULL;
  this->movement = movement;
  this->pixel = pixel;
  previous_command_millis = 0;
  was_running_millis = 0;
  headlight_mode = HEADLIGHT_MODE_AUTO;
  headlight_auto_state = HEADLIGHT_MODE_OFF;
}

void Controller::begin() {
  int status = WL_IDLE_STATUS;
  char ssid[] = "PP-GUEST";
  char pass[] = "myPassword"

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) { 
    return
  } else {
    server.begin();
    Serial.print("Connected to wifi. My address:");
    IPAddress myAddress = WiFi.localIP();
    Serial.println(myAddress);

  }
}

void Controller::parse() {
  String updown;
  String direction;
  int slash;
  // line is <up|down>/<forward|backward|left|right>
  // or      <turnspeed|forwardspeed|backwardspeed>/<speed>
  // or      headlightmode/
  slash = currentline.indexOf('/');
  if (-1 == slash) {
    // incomplete command
    currentline = "";
    return
  }
  updown = currentline.substring(0, slash);
  direction = currentline.substring(slash);
  if (updown == 'down') {
    if (direction == "forward") {
      m->go_forward();
    } else if (direction == "backward") {
      m->go_backward();
    } else if (direction == "left") {
      m->turn_left();
    } else if (direction == "right") {
      m->turn_right();
    }
  } else if (updown == 'up') {
    if (direction == "forward") {
      m->stop_forward();
    } else if (direction == "backward") {
      m->stop_backward();
    } else if (direction == "left") {
      m->stop_left();
    } else if (direction == "right") {
      m->stop_right();
    }    
  } else if (updown == 'turnspeed') {
    m->turn_speed = constrain(direction.toInt(), 0, 255);
  } else if (updown == 'forwardspeed') {
    m->forward_speed = constrain(direction.toInt(), 0, 255);
  } else if (updown == 'backwardspeed') {
    m->backward_speed = constrain(direction.toInt(), 0, 255);
  } else if (updown == 'headlightmode') {
    if (direction == 'kitmode')
    pixel->toggleKitLight(true);
    headlight_mode = HEADLIGHT_MODE_KITMODE;
  } else if (direction == "carlight") {
    pixel->toggleHeadLights(true);
    headlight_mode = HEADLIGHT_MODE_CARLIGHT;
  } else if (direction == "off") {
    pixel->toggleKitLight(false);
    headlight_mode = HEADLIGHT_MODE_OFF;
  } else if (direction == "auto") {
    headlight_mode = HEADLIGHT_MODE_AUTO;
    pixel.toggleKitLight(false);
  }
}

int Controller::pull() {
  char c;
  if (!client) {
    client = server.available();   // listen for incoming clients
    currentline = "";
  }

  if (!client) {
    m.stop()
    return
  }
  if (!client.connected()) {
    m.stop();
    return
  }
  
  while (client.available()) {     // if there's bytes to read from the client,
    c = client.read();             // read a byte, then
    if (c == '\n') {
      parse();
      break;
    } else {
      currentline += c;
    }
  }
}

void Controller::auto_control_headlight() {
  if (headlight_mode != HEADLIGHT_MODE_AUTO) {
    return;
  }
  unsigned long current_millis = millis();

  if (was_running_millis > current_millis) {
      // timer wrapped
      was_running_millis = 0;
  }

  if (movement.current_direction != 0) {
    // while moving, use headlights
    if (headlight_auto_state != HEADLIGHT_MODE_CARLIGHT) {
      pixel.toggleHeadLights(true);
      headlight_auto_state = HEADLIGHT_MODE_CARLIGHT;
    }
    was_running_millis = current_millis;
  } else {
    if (current_millis - was_running_millis >= 10200) {
      // sleep after 10 sec
      if (headlight_auto_state != HEADLIGHT_MODE_OFF) {
        pixel.toggleKitLight(false);      
        headlight_auto_state = HEADLIGHT_MODE_OFF;
      }
    } else if (current_millis - was_running_millis >= 1000) {
      // after 1 sec, show kit lights
      if (headlight_auto_state != HEADLIGHT_MODE_KITMODE) {
        pixel.toggleKitLight(true);
        headlight_auto_state = HEADLIGHT_MODE_KITMODE;
      }
    }
  }
}

