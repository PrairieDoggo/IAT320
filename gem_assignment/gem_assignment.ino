#include <Adafruit_CircuitPlayground.h>

int presets[3][3] = {
 {0,255,0},
 {255,0,0},
 {0,0,255}
};

void setup() {
 Serial.begin(9600);
 CircuitPlayground.begin();
}
void loop() {

 

float total = abs(CircuitPlayground.motionX()) + abs(CircuitPlayground.motionY()) + abs (CircuitPlayground.motionZ());
Serial.println(total);
delay(50);
if (total > 15) {

CircuitPlayground.setPixelColor(0, 56, 6, 138);
CircuitPlayground.setPixelColor(2, 56, 6, 138);
CircuitPlayground.setPixelColor(4, 56, 6, 138);
CircuitPlayground.setPixelColor(6, 56, 6, 138);
CircuitPlayground.setPixelColor(8, 56, 6, 138);
CircuitPlayground.setPixelColor(10,56, 6, 138);

CircuitPlayground.setPixelColor(1, 252, 245, 249);
CircuitPlayground.setPixelColor(3, 252, 245, 249);
CircuitPlayground.setPixelColor(5, 252, 245, 249);
CircuitPlayground.setPixelColor(7, 252, 245, 249);
CircuitPlayground.setPixelColor(9, 252, 245, 249);


}

if (total < 15) {




for (int i=0; i<10; i++) {
CircuitPlayground.setPixelColor(i, 222, 211, 11);


}

}

}
