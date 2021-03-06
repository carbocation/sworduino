
/* Confetti

  By: Mark Kriegsman

  Modified By: Andrew Tuline

  Date: July 2015

  Confetti flashes colours within a limited hue. It's been modified from Mark's original to support a few variables. It's a simple, but great looking routine.

*/


#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

// Fixed definitions cannot change on the fly.
#define LED_DT 7                                             // Data pin to connect to the strip.
//#define LED_CK 11                                             // Clock pin for the strip.
#define COLOR_ORDER GRB                                       // Are they RGB, GRB or what??
#define LED_TYPE WS2812B                                       // Don't forget to change LEDS.addLeds
#define NUM_LEDS 550                                           // Number of LED's.

// Initialize changeable global variables.
uint8_t max_bright = 255;                                      // Overall brightness definition. It can be changed on the fly.

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.

unsigned long previousMillis;                                 // Store last time the strip was updated.

// Define variables used by the sequences.
uint8_t  thisfade = 50;                                        // How quickly does it fade? Lower = slower fade rate.
int       thishue = 50;                                       // Starting hue.
uint8_t   thisinc = 1;                                        // Incremental value for rotating hues
uint8_t   thissat = 200;                                      // The saturation, where 255 = brilliant colours.
uint8_t   thisbri = 255;                                      // Brightness of a sequence. Remember, max_bright is the overall limiter.
int       huediff = 256;                                      // Range of random #'s to use for hue
uint8_t thisdelay = 1;                                        // We don't need much delay (if any)

void setup() {
  delay(3000);                                                // Power-up safety delay or something like that.
  Serial.begin(57600);

  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);    // Use this for WS2812B
  //  LEDS.addLeds<LED_TYPE, LED_DT, LED_CK, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2801 or APA102

  FastLED.setBrightness(max_bright);
  set_max_power_in_volts_and_milliamps(5, 6000);               // FastLED power management set at 5V, 500mA.
}


void loop () {


  EVERY_N_MILLISECONDS(1000) {                           // FastLED based non-blocking delay to update/display the sequence.
    ChangeMe();                                                 // Check the demo loop for changes to the variables.
    //    confetti();
  }

  confetti();

//  EVERY_N_MILLISECONDS(2000) {
//    flash();
//  }
  show_at_max_brightness_for_power();
}

void flash() {
  int flashes = 4;
  int ledstart = random16(NUM_LEDS);           // Determine starting location of flash
  int ledlen = random8(NUM_LEDS - ledstart);  // Determine length of flash (not to go beyond NUM_LEDS-1)
  fill_solid(leds, NUM_LEDS, CHSV(255, 0, 200));
  FastLED.show();
  fadeToBlackBy(leds, NUM_LEDS, 500);
  FastLED.show();
}

int numberOfSparkles = 1;
int increasing = true;

void confetti() {                                             // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds, NUM_LEDS, thisfade);                    // Low values = slower fade.

  //  int pos = random16(NUM_LEDS);                               // Pick an LED at random.
  //  leds[pos] += CHSV((thishue + random16(huediff)) / 4 , thissat, thisbri); // I use 12 bits for hue so that the hue increment isn't too quick.

  if (numberOfSparkles < 40 && increasing) {
    numberOfSparkles += 1;
  } else if (numberOfSparkles > 0) {
    numberOfSparkles -= 1;
    increasing = false;
  } else {
    increasing = true;
    numberOfSparkles += 1;
  }

//  if (numberOfSparkles == 0) {
//    flash();
//  }

  int pos;
  for (int i = 0; i < numberOfSparkles; i++) {
    pos = random16(NUM_LEDS);                               // Pick an LED at random.
    //    leds[pos] += CHSV((thishue + random16(huediff)) / 4 , thissat, thisbri); // I use 12 bits for hue so that the hue increment isn't too quick.
    leds[pos] = CHSV(thishue, thissat, thisbri);
  }


  thishue = thishue + thisinc;                                // It increments here.
}


void ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  //  uint8_t secondHand = (millis() / 1000) % 15;                // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
  //  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  //  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
  //    lastSecond = secondHand;
  //    switch(secondHand) {
  //      case  0: thisinc=1; thishue=192; thissat=255; thisfade=2; huediff=256; break;  // You can change values here, one at a time , or altogether.
  //      case  5: thisinc=2; thishue=128; thisfade=8; huediff=64; break;
  //      case 10: thisinc=1; thishue=random16(255); thisfade=1; huediff=16; break;      // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
  //      case 15: break;                                                                // Here's the matching 15 for the other one.
  //    }
  //  }
}
