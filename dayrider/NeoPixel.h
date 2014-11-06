/*
    NeoPixel.h - 
*/
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#ifndef NeoPixel_h
#define NeoPixel_h

#define KIT_LIGHT_DELAY 40 // in milliseconds


class NeoPixel : public Adafruit_NeoPixel {
  public:
    NeoPixel(uint16_t n, uint8_t p=6, uint8_t t=NEO_GRB + NEO_KHZ800);
    void toggleKitLight(bool enabled);
    void toggleHeadLights(bool enabled);
    void reset();
    void poll();

    void kitLightTimer(bool enabled);

  private:
    void kitLightNoTimer();
    uint16_t kitLightState;
    bool kitLightReverse;
    bool kitLightTrail;
    bool kitLightEnabled;
    unsigned long previous_millis;
};

#endif
