#include <Adafruit_CircuitPlayground.h>

//claim touch pad variables
int vals[7] = {3, 2, 0, 1, 10, 6, 9};

//claim note of pitches for each touch pad
float pitches[7] = {261.626, 293.665, 329.628, 349.228, 391.995, 440.0, 493.883};

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {

 //make each capcitance sensor play a different note
 for (int i = 0; i<7; i++){
  
  int x = CircuitPlayground.readCap(vals[i]);
 
  if(x > 600){
    
    //Play Sound
    CircuitPlayground.playTone(pitches[i], 100);
    
    }
 }
 
 delay(100);

}
