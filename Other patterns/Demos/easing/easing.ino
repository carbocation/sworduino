/* easing

By: Andrew Tuline
Email: atuline@gmail.com

Date: August, 2015

This simple program demonstrates the easing capability of FastLED. The Red LED starts out slow, speeds up and then slows down when it gets to the end.

It uses uint8_t variables:

easeOutVal = ease8InOutQuad(easeInVal);                       // Start with easeInVal at 0 and then go to 255 for the full easing.
ledNum = lerp8by8(0, NUM_LEDS, easeOutVal);                   // Map it to the number of LED's you have.

Ideas:
- Ease from 128 to 255 to throw something in the air
- Ease from 255 to 128 and reverse direction for it to fall back.
- Reduce the lerp8 value after each cycle to simulate a bouncing ball.
- Send me a real simple example.
- Profit!!!1!

*/


#include "FastLED.h"                                          // FastLED library. Please use the latest development version.

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

// Fixed definitions cannot change on the fly.
#define LED_DT 7                                             // Data pin to connect to the strip.
//#define LED_CK 11                                             // Clock pin for WS2801 or APA102.
#define COLOR_ORDER GRB                                       // It's GRB for WS2812 and BGR for APA102.
#define LED_TYPE WS2812                                       // Using APA102, WS2812, WS2801. Don't forget to change LEDS.addLeds.
#define NUM_LEDS 300                                           // Number of LED's.

// Global variables can be changed on the fly. 
uint8_t max_bright = 128;                                      // Overall brightness definition. It can be changed on the fly.

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.

int thisdelay = 1;

void setup() {
  delay(1000);                                                // Power-up safety delay.

//  LEDS.addLeds<LED_TYPE, LED_DT, LED_CK, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2801 or APA102
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);  // Use this for WS2812
  
  FastLED.setBrightness(max_bright);
  set_max_power_in_volts_and_milliamps(5, 500);               // FastLED Power management set at 5V, 500mA.
} // setup()

void loop() {
  EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
    easeMe();
  }
  show_at_max_brightness_for_power();                         // Keep this OUTSIDE the loop.
} // loop()


void easeMe() {

  static uint8_t easeOutVal = 0;
  static uint8_t easeInVal  = 0;
  static uint8_t lerpVal    = 0;

  easeOutVal = ease8InOutQuad(easeInVal);
  easeInVal++;

  lerpVal = lerp8by8(0, NUM_LEDS, easeOutVal);

  leds[lerpVal] = CRGB::Red;
  fadeToBlackBy(leds, NUM_LEDS, 16);                     // 8 bit, 1 = slow, 255 = fast
} // loop()
