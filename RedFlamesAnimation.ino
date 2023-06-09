#include <FastLED.h>

#define NUM_LEDS 28
#define LED_PIN 6

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // Create a "heat" array that will be used to generate the flame-like animation
  static byte heat[NUM_LEDS];
  const byte COOLING = 55;
  const byte SPARKING = 120;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }
  
  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if( random8() < SPARKING ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160,255) );
  }

  // Step 4.  Convert heat to LED colors
    for( int j = NUM_LEDS - 1; j >= 0; j--) {
    CRGB color = HeatColor( heat[j]);
    leds[j] = color;
  }

  // Step 5.  Display the colors on the LEDs
  FastLED.show();

  // Step 6.  Wait a little before starting the next animation frame
  delay(50);
}