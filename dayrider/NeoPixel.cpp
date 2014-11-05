#include <Adafruit_NeoPixel.h>
#include "NeoPixel.h"

NeoPixel::NeoPixel(uint16_t n, uint8_t p, uint8_t t) : Adafruit_NeoPixel(n, p, t) {
  kitLightState = 0;
}

void NeoPixel::toggleKitLight(bool enabled) {
  uint32_t color = 0xFF0000; // Hardcoded color to red
  int wait = 64;

  if (!enabled) {
  	reset();
   	return;
  }

  for (int i = 0; i < numPixels(); i++) {
    setPixelColor(i, color);
    show();
    delay(wait);
    if (i > 0) {
      setPixelColor(i-1, ((color & 0xFF0000) / 6) & 0xFF0000);
      setPixelColor(i-2, 0x000000);
    }
    show();
  }
  for (int i = numPixels() - 1; i >= 0; i--) {
    setPixelColor(i, color);
    show();
    delay(wait);
    if (i < numPixels()) {
      setPixelColor(i+1, ((color & 0xFF0000) / 6) & 0xFF0000);
      setPixelColor(i+2, 0x000000);
    }
    show();
  }
}

/**
 * This kit light method relies on exact timing in the main loop, 
 * preferable 40ms for the best effect
 */
void NeoPixel::kitLightNoTimer() {
  uint32_t color = 0xFF0000; // red color

  if (!kitLightReverse) {
    if (kitLightTrail && kitLightState > 0) {
      setPixelColor(kitLightState, color);
      setPixelColor(kitLightState - 1, ((color & 0xFF0000) / 6) & 0xFF0000);
      setPixelColor(kitLightState - 2, 0x000000);
      kitLightTrail = false;
    } else if (kitLightState < numPixels()) {
      setPixelColor(kitLightState, color);
      kitLightState++;
      if (kitLightState == (numPixels() - 1)) {
        kitLightReverse = true;
      } else {
        kitLightTrail = true;
      } 
    }
  } else {
    if (kitLightTrail && kitLightState < (numPixels() - 1)) {
      setPixelColor(kitLightState, color);
      setPixelColor(kitLightState + 1, ((color & 0xFF0000) / 6) & 0xFF0000);
      setPixelColor(kitLightState + 2, 0x000000);
      kitLightTrail = false;
    } else if (kitLightState >= 0) {
      setPixelColor(kitLightState, color);
      kitLightState--;
      if (kitLightState == 0) {
        kitLightReverse = false;
      } else {
        kitLightTrail = true;
      }
    }      
  }
  show();
}

void NeoPixel::toggleHeadLights(bool enabled) {
	if (enabled) {
		setPixelColor(0, 0xFFFFFF);
		setPixelColor(1, 0XFFFFFF);
		setPixelColor(numPixels() - 1, 0xFFFFFF);
		setPixelColor(numPixels() - 2, 0xFFFFFF);
		show();
	} else {
		reset();
	}
}

void NeoPixel::reset() {
	for (int i = 0; i < numPixels(); i++) {
		setPixelColor(i, 0x000000);
		show();
	}
}