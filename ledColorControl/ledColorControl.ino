/*
  LED Color Switch
  
  based on Button created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe
  This example code is in the public domain.
  http://www.arduino.cc/en/Tutorial/Button
*/

// constants won't change. They're used here to set pin numbers:
const int buttonPinRed = 3;     // the number of the pushbutton pin
const int buttonPinGreen = 5;   // the number of the pushbutton pin
const int buttonPinBlue = 6;    // the number of the pushbutton pin
const int buttonPinFlash = 4;

const int ledPinRed =  9;      // the number of the LED pin
const int ledPinGreen = 10;    // the number of the LED pin
const int ledPinBlue =  11;    // the number of the LED pin
const int blinkInterval = 500;  // 500 msec 

// variables 
int intensity = 128;      // max = 255; use PWM to reduce intensity 
unsigned long currTime = 0;
unsigned long prevTime = 0;
unsigned long previousMillis = 0;   // for builtin LED only - pulse
unsigned long prevBlinkTime = 0;    // for LED set that we control 
int prevState = 0;
int currState = 0;
int stateRed = 0;         // variable for reading the pushbutton status
int stateGreen = 0;       // variable for reading the pushbutton status
int stateBlue = 0;        // variable for reading the pushbutton status
int stateRedBlink = 0;
int stateGreenBlink = 0;
int stateBlueBlink = 0;
int blinkRate = 0;
int ledBuiltinState = LOW;

void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinRed, INPUT);
  pinMode(buttonPinGreen, INPUT);
  pinMode(buttonPinBlue, INPUT);
  currTime = millis();
}

void print3(String s1, int i1, String s2, int i2, String s3, int i3) {
  Serial.print(s1); Serial.print(i1);
  Serial.print(s2); Serial.print(i2);  
  Serial.print(s3); Serial.println(i3);  
}

void setLEDdark() {
    // turn all LED off:
    digitalWrite(ledPinRed, LOW);    
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinBlue, LOW);    
}

void setLEDcolor(int stateRed, int stateGreen, int stateBlue) {
  setLEDdark();
  if (stateRed > 0) {
    // turn specific color on; others off:
    analogWrite(ledPinRed, intensity);
  } if (stateGreen > 0) {
    analogWrite(ledPinGreen, intensity);
  } if (stateBlue > 0) {
    analogWrite(ledPinBlue, intensity);
  }
}

void blinkLEDset(unsigned int interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - prevBlinkTime >= interval) {
    // save the last time you blinked the LED
    prevBlinkTime = currentMillis;

    if(stateRed > 0) { // if the RED LED button is on
      // if the red LED is off turn it on and vice-versa:
      if (stateRedBlink > 0) {
        stateRedBlink = LOW;
      } else {
        stateRedBlink = intensity;
      }
      // set the LED with its current state 
      setLEDdark();
      analogWrite(ledPinRed, stateRedBlink);
    }
    if(stateGreen > 0) { // if the GREEN LED button is on
      stateGreenBlink = (stateGreenBlink > 0) ? LOW : intensity;
      setLEDdark();
      analogWrite(ledPinGreen, stateGreenBlink);
    }
    if(stateBlue > 0) { // if the BLUE LED button is on
      stateBlueBlink = (stateBlueBlink > 0) ? LOW : intensity;
      setLEDdark();
      analogWrite(ledPinBlue, stateBlueBlink);
    }
  }
}

void blinkBuiltinLED(unsigned long interval) {
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledBuiltinState == LOW) {
      ledBuiltinState = HIGH;
    } else {
      ledBuiltinState = LOW;
    }

    // set the LED with the ledBuiltinState of the variable:
    digitalWrite(LED_BUILTIN, ledBuiltinState);
  }
}

void loop() {
  currTime = millis();
  // read the state of the pushbutton value:
  stateRed = digitalRead(buttonPinRed);
  stateGreen = digitalRead(buttonPinGreen);
  stateBlue = digitalRead(buttonPinBlue);
  blinkRate = (digitalRead(buttonPinFlash) == HIGH) ? blinkInterval : 0;
  currState = (stateRed << 2) | (stateGreen << 1) | stateBlue;
  print3("currState=", currState, " prevState=", prevState, " blinkRate=", blinkRate);

  // check if any pushbutton is pressed. If it is, the state may change
  if( blinkRate == 0 ) {
    // set LEDs per requested state
    setLEDcolor(stateRed, stateGreen, stateBlue);
  } else {
    blinkLEDset(blinkInterval);  
  }
  
  blinkBuiltinLED(blinkInterval);
  prevState = (stateRed << 2) | (stateGreen << 1) | stateBlue;
  delay(10);  // cheap debounce
}
