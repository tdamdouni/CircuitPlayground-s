# Circuit Playground & Bluetooth Low Energy

_Captured: 2017-08-24 at 23:44 from [learn.adafruit.com](https://learn.adafruit.com/circuit-playground-and-bluetooth-low-energy?view=all)_

![circuit_playground_IMG_5098.jpg](https://cdn-learn.adafruit.com/assets/assets/000/034/546/large1024/circuit_playground_IMG_5098.jpg?1470197692)

[Circuit Playground](https://www.adafruit.com/product/3000) is an excellent all-in-one board for learning electronics, but did you know you can control Circuit Playground wirelessly from your phone or tablet? With the magic of Bluetooth Low Energy and a little helper like the [Flora Bluefruit LE module](https://www.adafruit.com/product/2487) you can start experimenting with wireless control of Circuit Playground today!

Adafruit's Bluefruit LE Connect apps for both iOS and Android provide a simple interface for controlling the digital inputs/outputs on Circuit Playground. Toggle digital pins high or low to control LEDs, relays, or other digital devices. Read digital inputs to detect when buttons are pressed or simple digital sensors activate. You can even control the color of the NeoPixels on Circuit Playground wirelessly from a few clicks in the app.

Best of all there's no soldering required for this project--just connect a few components with alligator clips and you're all set!

Before you get started you'll want to familiarize yourself with a few guides:

Continue on to learn about the parts needed to follow this guide.

![circuit_playground_IMG_5114.jpg](https://cdn-learn.adafruit.com/assets/assets/000/034/537/large1024/circuit_playground_IMG_5114.jpg?1470195557)

> _To follow this guide you'll need the following parts:_

    * I recommend using the [Flora Bluefruit LE module](https://www.adafruit.com/product/2487) with Circuit Playground because it has big pads that are easy to connect with alligator clips--no soldering necessary! You could however use a Bluefruit LE UART friend module but you'll need to solder headers or wires to it and Circuit Playground. **Be aware only Bluefruit LE modules with a serial connection (like Flora Bluefruit LE or Bluefruit LE UART Friend) will work with Circuit Playground!**
    * To reduce noise on the serial connection try to use short cables (less than 12" or so). Longer cables should still work but you might notice small glitches or errors from time to time.
  * **Android or iOS device with Bluetooth Low Energy support**
    * You'll need to run the Bluefruit LE Connect application from Adafruit which is available on both Android and iOS platforms. Make sure your device has Bluetooth Low Energy support (not just Bluetooth 'Classic' support, LE is different!). Most phones and tablets sold in the last ~5 years should have Bluetooth LE support.

If you're using the Flora Bluefruit LE module this project is very easy to put together and requires no soldering--just connect components with alligator clip wires as shown on the next page!

![circuit_playground_Wiring_Diagram_bb.png](https://cdn-learn.adafruit.com/assets/assets/000/034/196/large1024/circuit_playground_Wiring_Diagram_bb.png?1469124767)

![circuit_playground_IMG_5093.jpg](https://cdn-learn.adafruit.com/assets/assets/000/034/538/large1024/circuit_playground_IMG_5093.jpg?1470195924)

  * **Circuit Playground 3.3V** to **Flora Bluefruit LE 3.3V** (red wire).
  * **Circuit Playground GND** to **Flora Bluefruit GND** (black wire).
  * **Circuit Playground serial TX** to **Flora Bluefruit serial RX** (yellow wire). Double check you connect **TX to RX** and not TX to TX!
  * **Circuit Playground serial RX** to **Flora Bluefruit serial TX** (green wire). Again double check you connect **RX to TX** and not RX to RX!
  * **Circuit Playground #12** to **Flora Bluefruit MODE** (blue wire). You can actually use any of the other numbered pins on Circuit Playground for this mode switch connection, however you'll need to modify the examples to use the pin number. For simplicity stick with pin 12 so you don't need to modify the code in the rest of the guide.

Note if you're using a Bluefruit LE UART Friend the connections are the same but the MODE pin is labeled MOD, 3.3V is labeled VIN, RX is labeled RXI, and TX is labeled TXO. In addition you can ignore the other pins like CTS, RTS, and DFU.

**One last very important step is to flip the mode switch on the Flora Bluefruit LE module (or Bluefruit LE UART Friend) into the DATA position.** If the switch is in the CMD position the software won't work correctly so be careful to double check the switch is in DATA mode.

After wiring the Bluefruit LE module to Circuit Playground you'll need to do a small bit of software setup to run the examples.

First if you're new to Circuit Playground be sure to [follow its guide](https://learn.adafruit.com/../../../../introducing-circuit-playground) to setup Arduino for programming the board. Make sure you can load some of the basic examples like blinking a LED on the board before continuing further. Also don't forget to [install the Circuit Playground library](https://learn.adafruit.com/../../../../introducing-circuit-playground/libraries) in Arduino as the guide mentions.

Next follow the [Bluefruit LE module guide](https://learn.adafruit.com/../../../../adafruit-flora-bluefruit-le/overview) to install the necessary Arduino libraries for using the module. In particular you need to install this library (use the library manager in Arduino to search for and easily install it):

That should be all the setup necessary to program Circuit Playground with sketches that use a Bluefruit LE module! The next pages explain example sketches to control Circuit Playground with the Bluefruit LE module.

Pin IO is a way to control the digital inputs, outputs, and more on Circuit Playground wirelessly from a phone or tablet. Right now only basic components like digital inputs, outputs, and even PWM (i.e. dimming an LED) are controllable with pin IO.

Pin IO works using the [Firmata protocol](https://github.com/firmata/arduino) to remotely control the Circuit Playground. Normally Firmata is used with a USB or serial connection between an Arduino and a computer. However by hooking up a Bluefruit LE module to the serial pins on Circuit Playground you can wirelessly talk the Firmata protocol to control Circuit Playground too. You don't need to write any code to control the board--just load the Bluefruit LE Connect iOS or Android apps!

To use pin IO mode make sure you've followed all of the previous pages in this guide and have a Circuit Playground wired to a Bluefruit LE module, and the Arduino IDE setup to program both Circuit Playground and the Bluefruit LE module.

Next install the following Arduino library (use the library manager to find it, filter to **BLEFirmata** and install the Adafruit BLEFirmata library):

Once the library is installed open the **CircuitPlayground_nRF51822** example from the library in Arduino. This sketch implements the Firmata protocol and uses the Bluefruit LE module to listen for commands.

![circuit_playground_Screen_Shot_2016-08-02_at_8.48.21_PM.png](https://cdn-learn.adafruit.com/assets/assets/000/034/540/large1024/circuit_playground_Screen_Shot_2016-08-02_at_8.48.21_PM.png?1470196647)

You don't need to make any modificiations to the sketch to use it, however if you changed the mode pin from 12 to something else you will need to modify the **BLUEFRUIT_UART_MODE_PIN** define in the BluefruitConfig.h tab.

Upload the sketch to Circuit Playground and you should be ready to start controlling the pins with either the [Bluefruit LE Connect iOS app](https://itunes.apple.com/us/app/adafruit-bluefruit-le-connect/id830125974?mt=8) or [Bluefruit LE Connect Android app](https://play.google.com/store/apps/details?id=com.adafruit.bluefruit.le.connect). If you haven't used the Bluefruit LE Connect app before be sure to [skim the guide on its usage](https://learn.adafruit.com/../../../../bluefruit-le-connect-for-ios/pin-i-slash-o) (although the guide is for iOS that application is very similar on Android).

![circuit_playground_Screenshot_20160802-201631.png](https://cdn-learn.adafruit.com/assets/assets/000/034/541/medium800/circuit_playground_Screenshot_20160802-201631.png?1470197109)

Open the Bluefruit LE Connect application and look for a device called "**BLE_Firmata**". Click the **Connect** button to connect to the Bluefruit LE module.

![circuit_playground_Screenshot_20160802-201639.png](https://cdn-learn.adafruit.com/assets/assets/000/034/542/medium800/circuit_playground_Screenshot_20160802-201639.png?1470197179)

Click the **Pin I/O** button (on the iOS app look at the icons on the bottom of the screen) to enter Pin IO mode.

![circuit_playground_Screenshot_20160802-201650.png](https://cdn-learn.adafruit.com/assets/assets/000/034/543/medium800/circuit_playground_Screenshot_20160802-201650.png?1470197239)

After entering Pin IO mode you should see a list of the digital inputs & outputs on Circuit Playground.

![circuit_playground_Screenshot_20160802-201706.png](https://cdn-learn.adafruit.com/assets/assets/000/034/544/medium800/circuit_playground_Screenshot_20160802-201706.png?1470197307)

You can tap a pin to see options like turning it into an input and reading its state, or turning it into an output and setting it to a high or low logic level.

Try turning pin 13 into an output and toggling it high or low. This pin is actually connected to the red LED on Circuit Playground and you should see it turn on/off as the pin toggles.

Some of the components on Circuit Playground work just with digital IO and pin control:

  * The red LED on the board is pin 13 and can be turned on or off as a digital output.
  * The slide switch is pin 21 and will read a low level when on the right/+ and high level when on the left/-.
  * The left push button is pin 4 and right push button is pin 19, each will read a low level when not pressed and a high level when pressed.

Try pushing the buttons or moving the slide switch--you should see the pin state change in the Bluefruit LE Connect application. That's all there is to the basics of controlling digital pins wirelessly with Bluefruit LE & Circuit Playground!

In addition to toggling pins on Circuit Playground you can also control the color of its NeoPixel LEDs wirelessly from a phone or tablet. The Bluefruit LE Connect iOS and Android apps have a special color picker mode which makes it easy to change pixel colors.

To use this NeoPixel control sketch make sure you've followed all the steps in this guide and have a Circuit Playground wired up to a Bluefruit LE module. In addition make sure you have the Circuit Playground and Adafruit Bluefruit LE nRF51 Arduino libraries installed as [previously mentioned](https://learn.adafruit.com/../../../../circuit-playground-and-bluetooth-low-energy/software).

Next open the Arduino IDE and pick the **cplay_neopixel_picker** example from the **Adafruit Bluefruit LE nRF51 library.**

![circuit_playground_Screen_Shot_2016-08-02_at_3.38.47_PM.png](https://cdn-learn.adafruit.com/assets/assets/000/034/505/large1024/circuit_playground_Screen_Shot_2016-08-02_at_3.38.47_PM.png?1470177566)

You shouldn't need to modify anything in the sketch, however there are some #define values near the top that can adjust the behavior like the intensity of the NeoPixel brightness. Also if you changed the mode pin from 12 to something else you will need to modify the **BLUEFRUIT_UART_MODE_PIN** define in the BluefruitConfig.h tab.

Upload the sketch to Circuit Playground and you should be ready to start controlling the NeoPixels with either the [Bluefruit LE Connect iOS app](https://itunes.apple.com/us/app/adafruit-bluefruit-le-connect/id830125974?mt=8) or [Bluefruit LE Connect Android app](https://play.google.com/store/apps/details?id=com.adafruit.bluefruit.le.connect). If you haven't used the Bluefruit LE Connect app before be sure to [skim the guide on its usage](https://learn.adafruit.com/../../../../bluefruit-le-connect-for-ios/controller) (although the guide is for iOS that application is very similar on Android).

![circuit_playground_Screenshot_20160802-154233.png](https://cdn-learn.adafruit.com/assets/assets/000/034/547/medium800/circuit_playground_Screenshot_20160802-154233.png?1470198473)

On your iOS or Android device open the Bluefruit LE application. You should see a device called "**CPlay_BLE**" (sometimes in rare cases when the serial connection has too much noise you might see it called "**Adafruit Bluefruit LE**").

![circuit_playground_Screenshot_20160802-154243.png](https://cdn-learn.adafruit.com/assets/assets/000/034/548/medium800/circuit_playground_Screenshot_20160802-154243.png?1470198494)

Click the device, then click the **Controller** mode (**not** the NeoPixel mode, that's a more advanced NeoPixel control system that isn't supported by this sketch).

![circuit_playground_Screenshot_20160802-154255.png](https://cdn-learn.adafruit.com/assets/assets/000/034/549/medium800/circuit_playground_Screenshot_20160802-154255.png?1470198520)

Click the **Color Picker** at the bottom to enter the basic NeoPixel color picker control.

![circuit_playground_Screenshot_20160802-154305.png](https://cdn-learn.adafruit.com/assets/assets/000/034/551/medium800/circuit_playground_Screenshot_20160802-154305.png?1470198562)

Choose a color, then click **Send** to send it over Bluetooth Low Energy to Circuit Playground. You should see the NeoPixels on the board light up the chosen color!

![circuit_playground_Screenshot_20160802-154327.png](https://cdn-learn.adafruit.com/assets/assets/000/034/552/medium800/circuit_playground_Screenshot_20160802-154327.png?1470198583)

Finally go back to the **Controller** mode and select **Control Pad** at the bottom. Press the **left arrow** or **right arrow** to change which pixels are lit up.
