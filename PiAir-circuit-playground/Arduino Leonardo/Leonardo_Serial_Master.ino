/*
  Software serial multple serial test
 */
#include <SoftwareSerial.h>


SoftwareSerial mySerial(10, 11); // RX, TX
String Data = "";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Starting up!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello!");
  mySerial.listen();
}

int x = 0;
const String hash = "#";

void loop() { // run over and over

   mySerial.println(x);
   Serial.print(" Sent: ");
   Serial.println(x); 
   while (mySerial.available())
   {
        char character = mySerial.read(); // Receive a single character from the software serial port
        Data.concat(character); // Add the received character to the receive buffer
        if (character == '\n')
        {
            Serial.print("Received: ");
            Serial.print(Data);
            // x = Data.toInt()+1;  
            // Add your code to parse the received line here....

            // Clear receive buffer so we're ready to receive the next line
            Data = "";
        }
  }
  x++;
  if (x > 10) { x = 0;}
  delay(5000);  

}

