
 #include <Adafruit_CircuitPlayground.h>
#include <FastLED.h>
 
#define DATA_PIN     A1    //LED data on pin A1
#define NUM_LEDS    30   // total number of LEDs in my strip
#define COLOR_ORDER GRB  //  color order -- change this if my colors are coming out wrong

#define SLOUCH_ANGLE        10.0      // allowable slouch angle (deg)
#define SLOUCH_TIME         300      // allowable slouch time (secs) 
#define GRAVITY             9.80665   // standard gravity (m/s^s)
#define RAD2DEG             52.29578  // convert radians to degrees
 
uint8_t brightness = 50;  // Set brightness level
 
int STEPS = 3;  //makes the rainbow colors more or less spread out
int NUM_MODES = 2;  // change this number if you add or subtract modes
int CYCLETIME = 10;  // number of seconds on each mode, for mode cycling

int value;  //value from light sensor

// set up value for slouching angles
float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching;
 
CRGB leds[NUM_LEDS];      // set up an LED array
 
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
 
int ledMode = 0;       //Initial mode 
bool leftButtonPressed;
bool rightButtonPressed;
 
 
// SETUP -----------------------------------------------------
void setup() {
  // Initialize Circuit Playground and LED Strips
  Serial.begin(9600);
  CircuitPlayground.begin();
  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ); // Use this line if using neopixels
  currentBlending = LINEARBLEND;
  set_max_power_in_volts_and_milliamps(3, 3000);               // FastLED 2.1 Power management set at 3V, 3000mA
 
   // Initialize target angle to zero.
  targetAngle = 0;
}
 
void loop()  {
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
     
    // when wearer slouch
    if (slouching) {
      clearpixels();      //clear all initial light before the slouching action
      dangerLight();     //red light apears          
    }

    //set value to light sensor
    value = CircuitPlayground.lightSensor();

    //if light value is less than 30 (When it's dark)
    if (value < 30) {
      // clearpixels(); 
      ledMode=ledMode+1;
      delay(300);
        if (ledMode > NUM_MODES){
          ledMode=0;
        }
    }

    //if light value is more than 30 (When it's bright)
    if (value > 30){
      ledMode=99; //turn off light
    }
    
    // turn on green and blue light
    switch (ledMode) {        
       case 0: currentPalette = OceanColors_p; rainbow(); break;                    
       case 1: currentPalette = ForestColors_p; rainbow(); break;  
       case 99: clearpixels(); break;         
    }
}


void clearpixels(){
  CircuitPlayground.clearPixels();
   for( int i = 0; i < NUM_LEDS; i++) {
   leds[i]= CRGB::Black;
    }
   FastLED.show();
}
 
void rainbow(){
  
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
 
  FillLEDsFromPaletteColors( startIndex);
 
  FastLED.show();
  FastLED.delay(20); 
  }
 
//this bit is in every palette mode, needs to be in there just once
void FillLEDsFromPaletteColors( uint8_t colorIndex){ 
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += STEPS;
  }
}

int cycleMode=0;
void dangerLight(){
   switch (cycleMode) {
                         
       case 0: currentPalette = LavaColors_p; rainbow(); break;   
       case 5: cycleMode=0; break;
  }
}
