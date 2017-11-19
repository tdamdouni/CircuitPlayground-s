#include <Adafruit_CircuitPlayground.h>
String Data = "";

void setup() {
  CircuitPlayground.begin();  
  // initialize serial ports
  Serial.begin(9600);    // USB serial port 0
  Serial1.begin(9600);   // serial port 1
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  
  Serial.println("Setup complete");
}

byte rx_byte = 0;        // stores received byte
int x = 0;

void loop() {
  while (Serial1.available())
    {
        char character = Serial1.read(); // Receive a single character from the software serial port
        Data.concat(character); // Add the received character to the receive buffer
        if (character == '\n')
        {
            Serial.print("Received: ");
            Serial.print(Data);
            int x = Data.toInt();
            // Return the value + 1
            // Serial1.println(x+1);
            // Return x
            Serial1.println(x);
            Serial.print(" Returned: ");
            Serial.println(x);       
     
            CircuitPlayground.clearPixels();
            for (int i=0; i < x; i++){
                CircuitPlayground.setPixelColor(i, 0xFF0000);
              
            }
 
            // Clear receive buffer so we're ready to receive the next line
            Data = "";
        }
    }
  }
