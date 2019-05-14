#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

void setup() {
  // put your setup code here, to run once:
  #ifndef __AVR_ATtiny85__
    Serial.begin(9600);
    Serial.println("7 Segment Input Test");
  #endif
  matrix.begin(0x70);
}

void loop() {
  // put your main code here, to run repeatedly:
  int selectedValue = 2;
  
  float voltage = getAnalogVoltage(selectedValue);
  scaleVoltage(voltage, selectedValue);
  
//  float voltage = 0;
//  for(int i = 0; i < 500; i++) {
//    voltage = (float) i / 100;
//    scaleVoltage(voltage, selectedValue);
//    delay(50);
//  }
}

float getAnalogVoltage(int analogPin) {
  return analogRead(analogPin) * (5.0/1024.0);  
}

double scaleVoltage(float voltage, int selectedValue) {
  double value = 0.0;
  switch(selectedValue) {
    case 2:
      value = (1080.0 / 5.0) * voltage;
      matrix.println(value);
      break;
    case 1:
      value = (60.0 / 5.0) * voltage;
      matrix.println(value);
      break;
    case 0:
    default:
      matrix.clear();
      break;
  }
  matrix.writeDisplay();
  delay(150);
}
