#include <Adafruit_CircuitPlayground.h>

void setup() {
CircuitPlayground.begin();
pinMode(12, OUTPUT);

}

void loop(){
digitalWrite(12, HIGH);
}
