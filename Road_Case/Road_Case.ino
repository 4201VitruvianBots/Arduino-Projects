#include <LPD8806.h>
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
#include <avr/power.h>
#endif

const int
// Number of RGB LEDs in strand:
nLEDs = 255,
// Choose 2 pins for output; can be any valid output pins:
dataPin  = 2,
clockPin = 3,

COLOR_WIPE = 1,
THEATER_CHASE = 2,
SAFETY = 3,
RAINBOW = 4,
WHITE = 5;

int state = 0;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

void rainbow(uint8_t wait);
void colorWipe(uint32_t c, uint8_t wait);
void colorChase(uint32_t c, uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);
void colorFlash(uint32_t c, uint8_t wait);
uint32_t Wheel(uint16_t WheelPos);

void setup() {
  // put your setup code here, to run once:
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif

  Serial.begin(9600);
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  // strip.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(state){
    case COLOR_WIPE:
      colorWipe(strip.Color(0, 127, 0), 1); // Green
      break;
    case THEATER_CHASE:
      theaterChase(strip.Color(0, 127, 0), 50); // Green
      break;
    case SAFETY:
      colorChase(strip.Color(127, 75, 0), 1); // Yellow
      colorFlash(strip.Color(127, 75, 0), 1); // Orange
      break;
    case RAINBOW:
      rainbow(1);
      break;
    case WHITE:
    default:
      colorWipe(strip.Color(127, 127, 127), 1);
  }
  interruptCheck(); 
}

void interruptCheck(){
  bool interrupt = false;

  // Add an if statement for each button
  if(digitalRead(5) == HIGH && state != COLOR_WIPE){
    state = COLOR_WIPE;
    interrupt = true;
  }
  else if(digitalRead(6) == HIGH && state != THEATER_CHASE){
    state = THEATER_CHASE;
    interrupt = true;
  }
  else if(digitalRead(7) == HIGH && state != SAFETY){
    state = SAFETY;
    interrupt = true;
  }
  else if(digitalRead(8) == HIGH && state != RAINBOW){
    state = RAINBOW;
    interrupt = true;
  }
  else if(digitalRead(9) == HIGH && state != WHITE){
    state = WHITE;
    interrupt = true;
  }

  if(interrupt) // If any button is pressed, go back to loop() to change the state, else, continue with current routine.
    loop();
}

void rainbow(uint8_t wait) {
  for (int j = 0; j < 384; j++) {   // 3 cycles of all 384 colors in the wheel
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 384));
      interruptCheck();
    }
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    interruptCheck();
    strip.show();
    delay(wait);
  }
}

// Chase one dot down the full strip.
void colorChase(uint32_t c, uint8_t wait) {
  // Start by turning all pixels off:
  //  for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  // Then display one pixel at a time:
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    interruptCheck();
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(wait);
  }

  strip.show(); // Refresh to turn off last pixel
}

void theaterChase(uint32_t c, uint8_t wait) {
  //for (int j = 0; j < 10; j++){ //do 10 cycles of chasing. I don't know if this is really needed
    for (int q = 0; q < 3; q++){
      for (int i = 0; i < strip.numPixels(); i = i + 3){
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      interruptCheck();
      strip.show();
      
      delay(wait);
  
      for (int i = 0; i < strip.numPixels(); i = i + 3){
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  //}
}

//Hybrid of theaterChase and colorChase.
void colorFlash(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 3; j++) { //do 3 cycles of chasing
    for (int q = 0; q < 20; q++) {
      for (int i = 0; i < strip.numPixels(); i = i + 10) {
        strip.setPixelColor(i + q, c);  //turn every tenth pixel on
        interruptCheck();
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 10) {
        strip.setPixelColor(i + q, 0);      //turn every tenth pixel off
        interruptCheck();
      }
    }
  }
}

/* Helper functions */

//Input a value 0 to 384 to get a color value.
//The colours are a transition r - g -b - back to r

uint32_t Wheel(uint16_t WheelPos)
{
  byte r, g, b;
  switch (WheelPos / 128)
  {
    case 0:
      r = 127 - WheelPos % 128;   //Red down
      g = WheelPos % 128;      // Green up
      b = 0;                  //blue off
      break;
    case 1:
      g = 127 - WheelPos % 128;  //green down
      b = WheelPos % 128;      //blue up
      r = 0;                  //red off
      break;
    case 2:
      b = 127 - WheelPos % 128;  //blue down
      r = WheelPos % 128;      //red up
      g = 0;                  //green off
      break;
  }
  return (strip.Color(r, g, b));
}
