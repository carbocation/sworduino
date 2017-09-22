// Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsubd(x, b)  ((x>b)?255:0)
// Analog Unsigned subtraction macro. if result <0, then => 0
#define qsuba(x, b)  ((x>b)?x-b:0)

#define LED_DT 11
#define CLOCK_PIN 13
#define COLOR_ORDER BGR
#define LED_TYPE APA102
#define VOLTS 5
#define MAX_CURRENT_IN_MA 3000
#define NUM_LEDS 300
#define CIRCUMFERENCE 8
#define ROTATION_IN_MS 50000
#define FPS 24
#define DELAY (1000/FPS) // delay between each frame, in milliseconds
