/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>
#include <Adafruit_CircuitPlayground.h>

SoftwareSerial mySerial(10, 1); // RX, TX
String Data = "";

void setup() {
  CircuitPlayground.begin();  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Starting Up!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Shall we play a game?");
  mySerial.listen();
}

void loop() { // run over and over
  while (mySerial.available())
    {
        char character = mySerial.read(); // Receive a single character from the software serial port
        Data.concat(character); // Add the received character to the receive buffer
        if (character == '\n')
        {
            Serial.print("Received: ");
            Serial.print(Data);
            int x = Data.toInt();
            // Return the value + 1
            mySerial.println(x+1);
            Serial.print(" Returned: ");
            Serial.println(x+1);       
     
            CircuitPlayground.clearPixels();
            for (int i=0; i < x; i++){
                CircuitPlayground.setPixelColor(i, 0xFF0000);
              
            }
          

            // Clear receive buffer so we're ready to receive the next line
            Data = "";
        }
    }

 
}

