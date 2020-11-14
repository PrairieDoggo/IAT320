///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Slouch Detector v3
//
// Push button(s) to set a target angle.
// Compute current angle using accelerometer and compare
// to preset slouch angle. Sound alarm if slouching after
// a preset period of time.
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)
 
#include <Adafruit_CircuitPlayground.h>
 
#define SLOUCH_ANGLE        10.0      // allowable slouch angle (deg)
#define SLOUCH_TIME         300      // allowable slouch time (secs) 
#define GRAVITY             9.80665   // standard gravity (m/s^s)
#define RAD2DEG             52.29578  // convert radians to degrees
 
float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching;

///////////////////////////////////////////////////////////////////////////////
void setup() {
  // Initialize Circuit Playground
  CircuitPlayground.begin();
 
  // Initialize target angle to zero.
  targetAngle = 0;
}
 
///////////////////////////////////////////////////////////////////////////////
void loop() {
 
  //Brightness of Neopixel
   CircuitPlayground.setBrightness(10);
   
   //Turn ON all WHITE Neopixel LEDs as decoration
   for (int p=0; p<10; p++) {
    CircuitPlayground.setPixelColor(p, 255, 255, 255);
  }
  
  // Compute current angle
  currentAngle = RAD2DEG * asin(-CircuitPlayground.motionZ() / GRAVITY);
 
  // Set target angle on button press
  if ((CircuitPlayground.leftButton()) || (CircuitPlayground.rightButton())) {
    targetAngle = currentAngle;
    CircuitPlayground.playTone(900,100);
    delay(100);
    CircuitPlayground.playTone(900,100);
    delay(100);
    
  }
  
  // Check for slouching
  if (currentAngle - targetAngle > SLOUCH_ANGLE) {
    if (!slouching) slouchStartTime = millis();
    slouching = true;
  } else {
    slouching = false;
  }
 
  // If we are slouching
  // I add advanced feature which is blinking red LEDs and play tone while wearer is slouching
  if (slouching) {
    // Turn OFF all the WHITE Neopixel
    CircuitPlayground.clearPixels();

     // Turn ON all the RED NeoPixels
    for (int p=0; p<10; p++) {
    CircuitPlayground.setPixelColor(p, 255, 0, 0);
  }

    delay(SLOUCH_TIME);
   
      //Turn OFF all the NeoPixels
      CircuitPlayground.clearPixels();

       // Play a tone AFTER Blink
      CircuitPlayground.playTone(200, 500);   
      
            
  }
}
