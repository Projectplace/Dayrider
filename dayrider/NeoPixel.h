/*
    NeoPixel.h - 
*/
#include <Arduino.h>
#include <../../../../libraries/Adafruit_NeoPixel.h>

#ifndef NeoPixel_h
#define NeoPixel_h

class NeoPixel : public Adafruit_NeoPixel {
  public:
    NeoPixel(uint16_t n, uint8_t p=6, uint8_t t=NEO_GRB + NEO_KHZ800);
    void toggleKitLight(bool enabled);
    void toggleHeadLights(bool enabled);
    void kitLightNoTimer();
    void reset();

  private:
    int kitLightState;
    bool kitLightReverse;
    bool kitLightTrail;
};

#endif