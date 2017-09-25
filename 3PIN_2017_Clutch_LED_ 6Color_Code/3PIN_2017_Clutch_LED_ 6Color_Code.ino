/*
   Light entire LED strip in single color RED, GREEN, BLUE
   WS2812b - Digital RGB LED Pixel Strip -
   DC5V 60 LEDs per meter.  2.5 meters ==> 150 LEDs
   Library from Pololu https://github.com/pololu/pololu-led-strip-arduino

*/
#include <PololuLedStrip.h>
//#include <Bounce2.h>

/*
    ARDUINO PIN ASSIGNMENTS - double check these!
*/

#define RED_BUTTON  7
#define GREEN_BUTTON  8
#define BLUE_BUTTON 9
// 20170325 18:24 current wiring Yellow 6 Purple 4 
#define YELLOW_BUTTON 6
#define CYAN_BUTTON  5
#define PURPLE_BUTTON 4
#define LED_COUNT 150

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;
rgb_color colors[LED_COUNT];

#define RED   {127, 0, 0}
#define GREEN {0, 127, 0}
#define BLUE  {0, 0, 127}
#define BLACK {0, 0, 0}
#define WHITE {62, 62, 62}
#define YELLOW {90, 45, 0}
#define PURPLE {70, 0, 70}
#define CYAN   {0, 64, 64}

void displayColors(rgb_color c) {
  // OR (uint8_t r, uint8_t g, uint8_t b)
  // Create a buffer for holding the colors (3 bytes per color).
  rgb_color colors[LED_COUNT];
  for ( int i = 0; i < LED_COUNT; i++ ) {
    colors[i] = c;  // (rgb_color) {r, g, b};
  }
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);
  }

void displayScrolling(byte red, byte green, byte blue) {
    rgb_color colors[LED_COUNT];

    byte time = millis() >> 1;
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      byte x = time - 5 * i;
      colors[i] = (rgb_color) { x*red, x*green, x*blue};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);
}
    
void setup()
{
  pinMode(RED_BUTTON, INPUT);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT);
  pinMode(YELLOW_BUTTON, INPUT);
  pinMode(PURPLE_BUTTON, INPUT);
  pinMode(CYAN_BUTTON, INPUT);
  displayColors((rgb_color) CYAN);
}

void loop() {
  int testColor=0;
  if ( testColor==1 || digitalRead(RED_BUTTON) == HIGH ) {
    byte time = millis() >> 1;
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      byte x = time - 5 * i;
      colors[i] = (rgb_color) { x, 0, 0};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);
  }
  else if ( testColor==2 || digitalRead( GREEN_BUTTON ) == HIGH ) {
    byte time = millis() >> 1;
    for (uint16_t i = 0; i < LED_COUNT; i++)

    {
      byte x = time - 5 * i;
      colors[i] = (rgb_color) { 0, x, 0};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);
  }
  else if ( testColor==3 || digitalRead( BLUE_BUTTON ) == HIGH ) {
    byte time = millis() >> 1;
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      byte x = time - 5 * i;
      colors[i] = (rgb_color) { 0, 0, x};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);
  }
  else if ( testColor==4 || digitalRead( YELLOW_BUTTON ) == HIGH)  {
    byte time = millis() >> 1;
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      byte x = time - 5 * i;
      colors[i] = (rgb_color) { x, x/2, 0}; // less Green 
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);
  }
  else if ( testColor==5 || digitalRead(CYAN_BUTTON) == HIGH ) {
    byte time = millis() >> 1;
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      byte x = time - 5 * i;
      colors[i] = (rgb_color) {0, x, x};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);
  }
  else if ( testColor==6 || digitalRead( PURPLE_BUTTON ) == HIGH)  {
    // Update the colors.
    byte time = millis() >> 1;
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      byte x = time - 5 * i;
      colors[i] = (rgb_color) { x, 0, x};
    }
    // Write the colors to the LED strip.
    ledStrip.write(colors, LED_COUNT);  
  }
  // DEFAULT FALL THRU 
  else {
    displayColors((rgb_color) CYAN);
  }
  delay(1);
}

