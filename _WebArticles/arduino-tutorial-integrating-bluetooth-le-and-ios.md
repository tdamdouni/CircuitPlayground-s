# Arduino Tutorial: Integrating Bluetooth LE and iOS

_Captured: 2017-08-24 at 23:45 from [www.raywenderlich.com](https://www.raywenderlich.com/73306/arduino-tutorial-integrating-bluetooth-le-and-ios)_

Creating machines that interact with the physical world is an incredibly satisfying thing. Controlling them via Bluetooth with your iOS device is just plain awesome!

![Create an Arduino Bluetooth accessory!](https://koenig-media.raywenderlich.com/uploads/2014/06/Arduino_Bluetooth_250x250.svg_.png)

> _Create an Arduino Bluetooth accessory!_

In the past, the only way to create an Apple-approved Bluetooth device was by being part of the [MFi program](https://developer.apple.com/programs/mfi/). With [Bluetooth Low Energy 4.0](http://en.wikipedia.org/wiki/Bluetooth_low_energy), individuals and small companies can develop their own products and market them without the overhead of Apple's MFi regulations. That means you can talk to devices over Bluetooth LE with very little configuration and code, which opens up an entire world of opportunity for iOS developers.

This tutorial will teach you how to create your own Bluetooth LE device using standard off-the-shelf components that you can control wirelessly with a simple iOS app. Since the focus of this project is building a BLE device, you'll be using the iOS Core Bluetooth framework. If you're unfamiliar with Core Bluetooth, check out our [Introduction to Core Bluetooth: Building a Heart Rate Monitor](https://www.raywenderlich.com/52080/introduction-core-bluetooth-building-heart-rate-monitor) tutorial.

Let the building begin!

## Getting Started

Using off-the-shelf components for this build makes creating a Bluetooth device a snap. Here's an image showing the basic elements you'll use in this project:

![All Parts Needed](https://koenig-media.raywenderlich.com/uploads/2014/06/Parts-List.jpg)

> _A look at the parts you'll need to complete this project._

Here's the list of parts you'll need to complete the project, and where to obtain them:

  * iPhone 4s or newer with Bluetooth LE
![Arduino UNO](https://koenig-media.raywenderlich.com/uploads/2014/06/photo-3-e1402874471446.jpg)

  * [USB Mini-B Cable](https://www.sparkfun.com/products/11301), $3.95 at [SparkFun.com](http://sparkfun.com)  
![USB-b-mini](https://koenig-media.raywenderlich.com/uploads/2014/07/USB-b-mini.jpg)

![Servo](https://koenig-media.raywenderlich.com/uploads/2014/06/photo-1-e1402874546974.jpg)

![Jumper Wires](https://koenig-media.raywenderlich.com/uploads/2014/06/photo-2-e1402874487227.jpg)

![BLE Shield](https://koenig-media.raywenderlich.com/uploads/2014/05/IMG_2959-reduced.jpg)

_Note: _You can use a standard [Arduino Uno R3](https://www.sparkfun.com/products/11021) with a [USB A to B cable](https://www.sparkfun.com/products/512) if you already have one. Both will work with this BLE device.

The Arduino, servo and jumper wires can be purchased together from SparkFun.com in the [SparkFun Inventor's Kit for Arduino](https://www.sparkfun.com/products/12001). This kit comes with many useful components and tutorials to get you started in the hardware world.

You _can_ find less-expensive BLE Shields other than the one listed in this tutorial, but be aware that many of them sacrifice flexibility to save on cost. The BLE-Shield v2.0.0 allows you to program your own custom BLE Services and Characteristics onto the module. This means you can take full advantage of the Bluetooth 4.0 data structure.

That takes care of the hardware side of things - there's a few extra software pieces to take care of as well.

Download the [Xcode starter project here](https://koenig-media.raywenderlich.com/uploads/2014/08/Arduino_Servo_Starter.zip). The starter project includes the view controller and base Core Bluetooth implementation to save you time. You'll add more code to interface with the BLE Shield later on in the tutorial.

Next, download and install the Arduino IDE from the [Arduino Download](http://arduino.cc/en/Main/Software) page; it's available for Windows, Mac OS X and Linux platforms. You'll use the Arduino IDE to write and compile the code for the Arduino. Ensure you grab the latest _release_ version, not the beta or nightly builds.

_Note:_ Depending on the operating system and version of your Arduino board, you might need to install additional drivers in order to communicate with the Arduino. To see if you need to perform this extra step, check the [Getting Started with Arduino](http://arduino.cc/en/Guide/HomePage) page, select which operating system you're using and follow the step-by-step instructions provided.

## The Basic Design of your App

Your finished project will consist of an iOS app that will send messages via Bluetooth to the BLE Shield module. The module will then send the message to the Arduino board to tell the servo which position it should rotate to.

Here's an example use-case of your project:

  1. The user of the iOS app moves the slider to the middle position.
  2. The app sends the number 90, which represents 90 degrees in this case, to the BLE Shield module using the active Bluetooth connection.
  3. The BLE Shield transfers the number 90 to the Arduino board.
  4. The Arduino board rotates the servo to the 90 degree position.

Seems pretty straightforward! To begin, you'll work with the Arduino IDE and program the board logic.

_Note:_ The BLE Shield should _not_ be assembled onto the Arduino board at this time! You may encounter difficulty programming the Arduino if the BLE Shield is installed. As long as you remove it before programming the Arduino, everything should go smoothly. When you assemble or disassemble the BLE shield module or any of the wires, it's a good idea to remove power from the board by unplugging the USB cable first.

## Programming the Arduino

Start the Arduino IDE; you'll see the editor appear with a blank document, or "sketch", as shown below:

![Arduino IDE 001](https://koenig-media.raywenderlich.com/uploads/2014/06/Arduino-IDE-001.png)

Before doing anything else, click _File\Save_ in the top menu and save the current file to a convenient location as _Arduino_Servo_Controller_. This creates a folder in your save location that contains a file with a `.ino` file extension.

_Note: _Don't rename Arduino folders unless you also rename the .ino file contained within. The Arduino IDE requires that the .ino file reside in a folder with the same name.

Before you start writing code, you'll need to set up the IDE to communicate with the Arduino Uno board.

Select _Tools\Board\Arduino Uno_ to let the IDE know what kind of board you'll be dealing with. Next, connect the Uno to your computer with the USB cable as shown below:

![Arduino Kit](https://koenig-media.raywenderlich.com/uploads/2014/05/IMG_2952-reduced.jpg)

This lets the Arduino IDE recognize the serial port to which the Uno is connected.

_Note:_ The USB cable provides not only communication to the Arduino, but power as well. If you're working on a future project that requires more than 500mA, you'll have to use some other power source besides USB.

Once that's done, select _Tools\Serial Port\…_ and select the USB port the Arduino is connected to. Generally it's similar to _/dev/tty.usbserial…_ or _/dev/tty.usbmodem…_.

At this point the Arduino IDE is ready for programming.

Add the code below to your project using the Arduino IDE:
    
    
    // Arduino Bluetooth LE Servo Controlled by iOS
     
    void setup() // Called only once per startup
    { 
    } 
     
    void loop() // Continuous loop
    {
    }
    

Arduino programs are typically split into two main functions: `setup()` and `loop()`.

The `setup()` function does exactly what it is says: it's called only once on startup and is a great place for setting up your hardware and software. The `loop()` function is called once `setup()` is done. Once you enter `loop()` you never exit, but continually execute the code within in linear order until the board is reset or powered down.

Click the Verify button (the checkmark icon) to ensure everything compiles correctly. If so, you'll see a confirmation message similar to below:

![BLE-Success-Build](https://koenig-media.raywenderlich.com/uploads/2014/07/BLE-Success-Build.png)

Now that you have the basic framework of the Arduino program in place, it's time to add some logic to control the board.

## Illuminating an LED

The main objective of your Arduino program in this project is to receive the one-byte messages coming from the BLE Shield and use the contents of the message to set the servo's position. But before you get too involved into the servo code, it would be nice to test your current connections.

The easiest way to do this is to write a small program that controls the built-in LED on the Uno. Think of it as the "hello world" equivalent on the Arduino. :]

Replace the code in your project with the following:
    
    
    // Arduino Bluetooth LE Servo Controlled by iOS
    
    int LED = 13;     // Most Arduino boards have an onboard LED on pin 13
    
    void setup()  // Called only once per startup
    { 
      pinMode(LED, OUTPUT);     // Set pin as an output
      digitalWrite(LED, HIGH);  // Turn on LED (ie set to HIGH voltage)
    } 
    
    void loop() // Continuous loop
    {
      delay(500);
      digitalWrite(LED, LOW);
      delay(500);
      digitalWrite(LED, HIGH);
    }
    

Since most Arduino boards have an onboard LED on pin 13, you can use the illumination of the LED as confirmation that your Arduino program is executing properly. You set the `LED` variable to 13 to refer to that pin.

In `setup()`, you set the initial state of the board. `pinMode(LED, OUTPUT)` sets pin 13 as a digital output, which means that the voltage on this pin can be set to HIGH (+5v) or LOW (0v). `digitalWrite()` sets the pin's voltage; in the code above you've set it to HIGH to illuminate the LED.

After `setup()` has finished, `loop()` will run continuously. `delay()` will wait a certain number of milliseconds which you'll use to get the LED to blink. After a 500ms delay, you turn the LED off by writing the value LOW; after another delay, you turn the LED back on.

Click the _Verify_ button again to compile the program and check for any syntax errors. If your program compiles without issue, you'll see _Done Compiling_ in the status bar of the Arduino IDE. If not, read the status bar message for an indication of where you've messed up, fix the error and click the _Verify_ button to make sure you've squashed the bug for good.

Now it's time to program the code to the Arduino board and test the LED.

Make sure your Arduino is connected to your computer with the USB cable then click the _Upload_ button (the one with the right arrow icon) to program the Arduino board. Once the upload process has finished, the _Done uploading_ message should appear in the status bar as shown below:

![Click Upload. Done uploading. Success!](https://koenig-media.raywenderlich.com/uploads/2014/06/Screen-Shot-2014-06-24-at-8.13.13-AM.png)

Check your Arduino board, and you should see the LED start to blink.

![LED 13 is ON. Houston we have communication.](https://koenig-media.raywenderlich.com/uploads/2014/06/IMG_4476-reduced-669x500.jpg)

> _LED 13 is ON. Houston, we have communication._

If an error occurred, try the following things to diagnose your issue:

  * Check that _Arduino Uno_ is selected in the _Tools/Board_ menu.
  * Check that _/dev/tty.usbserial…_ or _/dev/tty.usbmodem…_ (or similar) is selected in the _Tools/Serial Port_ menu.
  * Check that you installed any required drivers for your Arduino board as noted earlier.
  * Check that the BLE Shield is _not_ assembled on the Arduino board during programming of the board.

If the LED works, you can be sure that the Arduino IDE is set up properly. You can now add some code to control the servo.

## Interfacing With the Servo Control

A _servo_ is a motor with a changeable rotational position. You control a servo by sending different frequencies of electric pulses to its control line.

Replace the blinking LED code in the current sketch with the following:
    
    
    // Arduino Bluetooth LE Servo Controlled by iOS
    
    #include <Servo.h>
    
    int LED = 13;     // Most Arduino boards have an onboard LED on pin 13
    Servo myservo;    // Create servo object to control the servo
    

The above code imports the `Servo` library and create a variable as an instance of the `Servo` class. By including the `Servo` library, you can create `Servo` objects which can be easily configured to control the servo hardware.

Next, add the following function:
    
    
    void setup()  // Called only once per startup
    { 
      pinMode(LED, OUTPUT);     // Set pin as an output
      digitalWrite(LED, HIGH);  // Turn on LED (ie set to HIGH voltage)
    
      myservo.attach(9);        // Attach the servo object to pin 9
      myservo.write(0);         // Initialize servo position to 0
    } 
    

`myServo.attach(9)` indicates that output pin 9 of the Arduino Uno board will be connected to the servo, while `write(0)` sets the position of the servo to zero degrees.

That takes care of the servo initialization, but you'll still need some code to handle the BLE communication. Before you tackle that, you should read through the following section on the fundamentals of serial communication.

## Serial Communication

Serial communication is much like using a telephone. The speaker held to your ear is the receiver (RX) and the microphone is the transmitter (TX). Your transmitter is connected to the receiver of the person with whom you are talking, and your receiver is connected to their transmitter. This allows for bi-directional communication where either person can send or receive information.

_Note: _The Arduino's Serial Port communicates using standard TTL voltage levels (0-5v). This type of communication requires three connections: transmit (TX), receive (RX), plus a common ground. The BLE Shield was designed to communicate with the Arduino's serial port; therefore, its TX line will connect to the Arduino's RX port and, conversely, its RX line will connect to the Arduino's TX port.

By default, the Arduino uses pin 0 and pin 1 for serial communication. To communicate with the BLE Shield, this needs to be changed to pin 4 (RX) and pin 5 (TX). This guards against any data collision when the PC is uploading to the Arduino.

Add the following include to the top of the file:
    
    
    #include <SoftwareSerial.h>
    

This will allow you to use the serial communication library.

Add the following variable underneath the LED and myservo variable declarations:
    
    
    SoftwareSerial BLE_Shield(4,5);
    

This will create an instance of `SoftwareSerial` named `BLE_Shield`. The two parameters are pin numbers, so the BLE shield will use RX and TX lines 4 and 5 respectively.

Add the following line to the end of the `setup()` function:
    
    
    BLE_Shield.begin(9600);   // Setup the serial port at 9600 bps. This is the BLE Shield default baud rate. 
    

This sets the serial communication, or _baud_ rate, which is the speed at which data bits are transmitted. In order for two devices to communicate, they must use the same baud rate. Since the BLE Shield's default baud rate is 9600, you set the Arduino serial port to match.

Finally, add the following function to the bottom of the sketch:
    
    
    void loop()  // Continuous loop
    {
      // See if new position data is available
      if (BLE_Shield.available()) {
        myservo.write(BLE_Shield.read());  // Write position to servo
      }
    }
    

Eventually, your iOS device will be feeding data to the BLE shield. `loop()` has one job now: look for new bytes from the BLE shield's RX line and pass them to the servo.

First, it calls `BLE_Shield.available()` to see if any bytes are available. If so, read the available bytes and write them to `myServo`. If there is no new data from the BLE Shield, then it loops around and checks again…and again…and again.

Save your Arduino project then click the _Upload_ button to upload your new program to the Arduino board. The _Done uploading_ message should appear at the bottom of the IDE. You'll see the LED light up and stay lit, letting you know `main()` finished.

At this point, your Arduino code is complete and ready for communication with your iOS app via the BLE Shield.

The next logical step is to get familiar with how the BLE Shield functions; you'll cover this in the next section.

## The Inner Workings of the BLE Shield

The BLE Shield V2.0.0 from Seeed Studio is based on Bluegiga's BLE112 module which supports Bluetooth Low Energy 4.0. The BLE112, with or without the Shield component, is a great module for interfacing with iOS devices. It can be programmed with custom scripts to run without the need for an additional processor.

In this project, you'll focus on using the BLE Shield as comes out of the box. It's preprogrammed with a BLE Service and some characteristics geared toward basic communication.

What type of communication do you think will be used between the Arduino board and BLE Shield? Hint: The answer was mentioned earlier in the _Serial Communication_ section.

Here are the preprogrammed Service and Characteristics that come with this specific BLE device as found in the [BLE-Shield firmware repository on GitHub](https://github.com/michaelkroll/BLE-Shield/blob/master/firmware/BLE-Shield-v2.0.0/BLE-Shield_gatt.xml):

  * Service  
Name: _BLE Shield Service v2.0.0_  
UUID: _B8E06067-62AD-41BA-9231-206AE80AB550_
  * Characteristic  
Name: _Bluetooth Device Address_  
UUID: _65C228DA-BAD1-4F41-B55F-3D177F4E2196_
  * Characteristic  
Name: _RX_  
UUID: _F897177B-AEE8-4767-8ECC-CC694FD5FCEE_  
Description: The RX characteristic is used to receive data on the iOS Side. Data written to the BLE-Shield's TX pin will be notified on the RX characteristic on the iOS device.
  * Characteristic  
Name: _TX_  
UUID: _BF45E40A-DE2A-4BC8-BBA0-E5D6065F1B4B_  
Description: The iPhone sends data to the BLE-Shield's TX characteristic which is then received on the RX pin of the BLE-Shield. The maximum amount of data which can be sent at once is 20 bytes due to BLE112 restrictions.
  * Characteristic  
Name: _Baudrate_  
UUID: _2FBC0F31-726A-4014-B9FE-C8BE0652E982_  
Supported baud rate values:  
0×00 = 9600 Baud (default)  
0×01 = 14400 Baud  
0×02 = 19200 Baud   
0×03 = 28800 Baud  
0×04 = 38400 Baud

Since your project is based on one-way communication from your iOS device to the Arduino board, you'll only make use of the TX characteristic.

## Hardware Connections

Now it's time to work on the hardware connections of the project. Be sure the _USB cable is unplugged_ from the Arduino board before working with the hardware.

_Note:_ The Arduino saves the last-uploaded sketch to its internal memory. The next time you connect the USB cable, the sketch you just wrote will run automatically without clicking the Upload button from the Arduino IDE!

To make your life easier, gather the following parts below before you begin:

  * Arduino Uno Board
  * BLE-Shield
  * Servo
  * Three jumper wires

The first place to start is configuring the RX/TX jumpers. The BLE Shield default jumper position connects its RX to pin 0 and TX to pin 1. To match the Arduino code above, you'll need to set RX to pin 4 and TX to pin 5.

Move the jumpers on the board to the appropriate pins as indicated in the image below:

![Move BLE Shield Jumpers RX and TX to the indicated positions.](https://koenig-media.raywenderlich.com/uploads/2014/08/BLE-Shield-Jumpers-new.jpg)

> _Move BLE Shield Jumpers RX and TX to the indicated positions._

Assemble the BLE Shield onto the Arduino board as shown below:

![Attaching BLE Shield to Arduino board](https://koenig-media.raywenderlich.com/uploads/2014/06/IMG_4477-reduced-669x500.jpg)

> _Attaching BLE Shield to Arduino board_

Be sure to match up the pins before applying any pressure to seat the BLE Shield. Inserting misaligned pins can cause damage to the hardware.

Once you're done, the entire assembly should look like this:

![BLE Shield Assembled!](https://koenig-media.raywenderlich.com/uploads/2014/06/IMG_3497-reduced.jpg)

> _BLE Shield Assembled!_

The servo motor requires three connections: +5v (red), Ground (black) and Position Signal (white). The +5v and Ground connections provide the servo with the power it needs to change and maintain its rotational position. The Position Signal connection is used to set the position of the servo. To prevent possible damage to the servo, ensure you don't swap any of the connections.

_Note: _A servo's position is based on the frequency of electric pulses sent to the servo's Position Signal wire. If you were to connect this wire to an oscilloscope you would see a square wave pattern with a specific frequency and duty cycle. As the frequency changes, the servo motor turns its shaft according to the frequency of the received pulse.

Attach the three wires to the servo motor as shown in the image below:

![Assembled Servo Wires](https://koenig-media.raywenderlich.com/uploads/2014/05/IMG_2955-reduced.jpg)

It's a good idea to use the same color wires as the servo leads so that you don't get mixed up as to which wire goes where.

Connect the _red wire_ to the BLE Shield's _5v pin_. Connect the _black wire_ to the _GND_ pin and the _white wire_ to _pin 9_ as shown below:

![Wires Connected to BLE Shield](https://koenig-media.raywenderlich.com/uploads/2014/06/IMG_3498-reduced.jpg)

> _Wires Connected to BLE Shield_

Your hardware is connected and ready to go. All that's left is to finish writing your iOS app to tie it all together!

## Fleshing out the iOS App

The app uses a slider to wirelessly control the position of the servo. When you move the slider button up and down, the position data will be sent to the Arduino's BLE Shield. The Connect/Disconnect icon at the bottom will indicate the Bluetooth connection status.

Open the [downloaded starter project](https://koenig-media.raywenderlich.com/uploads/2014/08/Arduino_Servo_Starter.zip) in Xcode, plug in your iPhone and build and run your app. The app will open and you will see an image similar to the one below:

![Arduino Servo App](https://koenig-media.raywenderlich.com/uploads/2014/06/IMG_0942.png)

> _Arduino Servo App_

The app isn't quite ready to communication with the Arduino, but that's where you come in.

Click the _Stop_ button in Xcode.

## Starter Project Overview

When the app starts, `RWTViewController` creates an instance of `BTDiscovery` to begin searching for BLE devices in range with a specific Service UUID. `BTDiscovery` manages the discovery of and connections to Bluetooth devices. It also notifies the app when a Bluetooth device connects or disconnects.

`RWTViewController` has a vertical slider control that sends the slider's position value to _BTService_ and updates the Bluetooth image with the connection status. _BTService_ handles the communication to the BLE shield module.

Before moving on, open _BTService.h_ -- there are a few important things in this file that help the app communicate with the BLE Shield, so it's worth taking a minute to review them.

Towards the top of the file you'll see a couple of UUID `#defines`.

`RWT_BLE_SERVICE_UUID` represents the 128-bit service UUID of the Arduino's BLE Shield. You'll notice that this UUID matches the BLE Shield Service v2.0.0 UUID listed earlier in the tutorial. Similarly, `RWT_POSITION_CHAR_UUID` matches the BLE Shield's TX UUID. Both hex values must match in order for the app to discover and communicate with the BLE Shield.

Finally, `RWT_BLE_SERVICE_CHANGED_STATUS_NOTIFICATION` notifies the rest of the app when a peripheral connects or disconnectes from the app. The main view controller of your app uses this value to toggle the connection image on the home screen.

No code needs to be added here, so you can move on.

Open _RWTViewController.m_ and replace the implementation of `sendPosition:` with the following:
    
    
    - (void)sendPosition:(uint8_t)position {
      // Valid position range: 0 to 180
      static uint8_t lastPosition = 255;
      
      if (!self.allowTX) { // 1
        return;
      }
      
      // Validate value
      if (position == lastPosition) { // 2
        return;
      }
      else if ((position < 0) || (position > 180)) { // 3
        return;
      }
      
      // Send position to BLE Shield (if service exists and is connected)
      if ([BTDiscovery sharedInstance].bleService) { // 4
        [[BTDiscovery sharedInstance].bleService writePosition:position];
        lastPosition = position;
        
        // Start delay timer
        self.allowTX = NO;
        if (!self.timerTXDelay) { // 5
          self.timerTXDelay = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(timerTXDelayElapsed) userInfo:nil repeats:NO];
        }
      }
    }
    

This method is called from `positionSliderChanged:` each time the user moves the slider. Here's what happens in this method:

  1. Only continue if no other send occurred in the last 0.1 seconds to avoid flooding the BLE connection with too much data.
  2. Prevent the same value from being written multiple times. To keep traffic and power use to a minimum, you always want to take advantage of any opportunity to prevent sending duplicate data.
  3. Make sure that the values being sent are in the correct range. The Arduino's Servo object accepts values between 0 and 180. If you take a peek at the storyboard file, you will see that the slider's minimum and maximum values have been set to the same range.
  4. Ensure that the `BTService` exists and is ready for action, then write the slider value to the position characteristic.
  5. The timer prevents you from flooding the BLE Shield with data. First, you set `self.allowTX` to `NO` while sending data to the shield and then reset it back to `YES` after the delay.

_Note:_ What's the significance of using a timer here? Well, BLE devices are low energy devices -- which translates into "low horse power". Also recall that the baud rate between the Arduino and the BLE Shield is set at 9600 bps. If you are building an application with large volumes of data, increase the baud rate if you can to preserve energy.

Now you have to implement the part of `BTService` to transmit the data. Open _BTService.m_ and replace the implementation of `writePosition:` with the following:
    
    
    - (void)writePosition:(UInt8)position {
      // See if characteristic has been discovered before writing to it
      if (!self.positionCharacteristic) {
        return;
      }
    
      NSData *data = nil;
      data = [NSData dataWithBytes:&position length:sizeof(position)];
      [self.peripheral writeValue:data
                forCharacteristic:self.positionCharacteristic
                             type:CBCharacteristicWriteWithResponse];
    }
    

To start, the method will return immediately if the proper characteristic matching the UUID in _BTService.h_ hasn't been discovered yet. If it has, you need to wrap the data -- simply the `position` value -- in an `NSData` object. Then, you write the value out to the Core Bluetooth peripheral.

Since your `positionCharacteristic` UUID matches the BLE Shield's TX characteristic, the BLE Shield transmits the data to the RX of the Arduino. The Arduino code written earlier uses this piece of data to set the servo's position.

Build your app to make sure everything compiles. You app is now complete and ready for testing!

## Putting it All Together

The Arduino, BLE Shield, and servo should already be fully assembled as shown in the image below:

![Arduino Servo Project Completed!](https://koenig-media.raywenderlich.com/uploads/2014/06/IMG_4013-reduced.jpg)

> _Arduino Servo Project Completed!_

Plug the USB cord into the Arduino to supply power. Next make sure your iPhone's Bluetooth is on and your iPhone is connected to your computer.

Run your app from Xcode; within a couple seconds you should see the app's Bluetooth icon change from _Disconnected_ to _Connected_ and the BLE Shield's LED should illuminate. Now move the slider up and down. You should see the servo motor rotate based on the slider movement.

(Here's a direct link to the [QuickTime movie file](https://koenig-media.raywenderlich.com/uploads/2014/06/IMG_4576-reduced.mov) if you can't see the above action video.)

## Where To Go From Here?

You can download the final project [here](https://koenig-media.raywenderlich.com/uploads/2014/07/Arduino_Servo_Final.zip); it includes both the iOS and the Arduino code.

Hopefully this project has spurred you to dream up other projects that use Bluetooth LE devices and iOS. For example, you could use this tutorial's servo motor to automatically unlock the front door of your house. Or, you could create an iOS remote control for your water sprinklers and never forget to water your lawn again!

This project gave you a small taste of what it takes to create your own BLE device. If you're interested in learning more about this topic, you might enjoy my book _Integrating iOS Bluetooth LE with PIC18 Microcontrollers_. It gives an in-depth look at creating a BLE device at the microcontroller level.

As well, the book provides practical lessons on how to program and configure your own Services and Characteristics for machine control. The main project of the book is based on the iO Xtreme PCB. The book and the iO Xtreme board are available on my website at [www.back-40.com](http://www.back-40.com).

I hope you enjoyed the tutorial. If you have any questions or comments, please join the discussion in the forums!
