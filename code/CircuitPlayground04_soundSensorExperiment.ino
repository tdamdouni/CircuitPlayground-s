/** 
  Sound Sensor with Neo Pixel indicator.
  this little sketch correlates the MEMs Microphone onthe board to the nep pixels for out put. 
  the sketch also tries to perform a rough attempt at dynamically changing the max and min ranges to keep the neo pixels lively
  should the ambient sound change.
  
  developed by Keith Makan (@k3170makan)
  https://www.adafruit.com/product/3000 
**/
#include <Adafruit_CircuitPlayground.h>
int base_max = 340;
int base_min = 300;
int max_dx_count = 0;
int min_dx_count = 0;
int loop_count = 0;
int max_sound = 0;
int max_sound_prev = 0;
int min_sound = 1000;
int min_sound_prev = 0;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    CircuitPlayground.begin();
    //startup animation
    int i = 0;
    int numPixels = CircuitPlayground.strip.numPixels(); 
    for(i=0;i<=numPixels-1;i++){
      CircuitPlayground.setPixelColor(i,100-i*10,250,100-i*10);
      delay(100);
    }
    CircuitPlayground.clearPixels();
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_count = (loop_count + 1) % 100;
  Serial.print(loop_count);Serial.print("] ");
  Serial.print("Sound Sensor: "); Serial.print(CircuitPlayground.soundSensor());
  int soundLevel = CircuitPlayground.soundSensor();
  
  if (soundLevel > max_sound){
      max_dx_count = soundLevel - max_sound;
      max_sound = soundLevel;

  }
  if (soundLevel < min_sound){
    min_dx_count = min_sound - soundLevel;
    min_sound = soundLevel;
  }
  if (loop_count == 0){ //after 100 loops check that the rate of change is good
     if (max_dx_count <= 20){
        max_sound = base_max;
        max_dx_count = 0;
     }
     if (min_dx_count <= 20){
        min_sound = base_min;
        min_dx_count = 0;
     }
  }
  Serial.print(" max sound: "); Serial.print(max_sound);
  Serial.print(" min sound: "); Serial.print(min_sound);
  Serial.print(" max_dx: "); Serial.print(max_dx_count);
  Serial.print(" min_dx: "); Serial.println(min_dx_count);
  
  
  int numPixels = CircuitPlayground.strip.numPixels();
  int pixelLimit = map(soundLevel,min_sound,max_sound,0,10); //input the sound level (determined from random testing) and output a value determined by the range observed through loose testing in a random starbucks in mountain view
    //should try to determine the ambient level maybe?
    for (int i = 0;i <= pixelLimit; i++){

       CircuitPlayground.setPixelColor(i,255,20-i*2,20-i*2);
    }
    delay(50);
    CircuitPlayground.clearPixels();
}