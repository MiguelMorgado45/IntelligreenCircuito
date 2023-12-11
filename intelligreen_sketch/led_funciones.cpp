#include "led_funciones.h"

#define NUM_LEDS 8
#define DATA_PIN 23

CRGB leds[NUM_LEDS]; 

void configurarLeds() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
}

void encenderLeds(int estado) {
  int index;
  if (estado <= 3) {
    index = 1;
  } else if (estado <= 6) {
    index = 2;
  } else if (estado <= 7) {
    index = 0;
  }

  apagarLeds(index);
  // 1 a 3 - Internet
  if (estado == 1) {
    for (int i = 1; i < 8; i++) {
      leds[i] = CRGB::BlueViolet;
      FastLED.show();
      delay(100);
    }
  }
  if (estado == 2) {
    leds[1] = CRGB::BlueViolet;
    FastLED.show();
  }
  if (estado == 3) {
    leds[1] = CRGB::Red;
    FastLED.show();
  }

  // 4 a 6 - MQTT
  if (estado == 4) {
    for (int i = 2; i < 8; i++) {
      leds[i] = CRGB::Orange;
      FastLED.show();
      delay(100);
    }
  }
  if (estado == 5) {
    leds[2] = CRGB::Orange;
    FastLED.show();
  }
  if (estado == 6) {
    leds[2] = CRGB::Red;
    FastLED.show();
  }

  // 7 a 9 - Bluetooth
  if (estado == 7) {
    for(int i = 0; i < 8; i++) {
      leds[i] = CRGB::Blue;
      FastLED.show();
      delay(100);
    }
  }

  if (estado == 8) {
    leds[0] = CRGB::Blue;
    FastLED.show();
  }

  if (estado == 9) {
    leds[0] = CRGB::Red;
    FastLED.show();
  }
}

void apagarLeds(int index) {
  for(int i = index; i < 8; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}