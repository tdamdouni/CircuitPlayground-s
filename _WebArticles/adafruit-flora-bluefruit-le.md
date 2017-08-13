# Adafruit Flora Bluefruit LE

_Captured: 2017-08-08 at 08:28 from [learn.adafruit.com](https://learn.adafruit.com/adafruit-flora-bluefruit-le?view=all)_

![adafruit_products_2487_hand_demo_ORIG.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/363/large1024/adafruit_products_2487_hand_demo_ORIG.jpg?1431372712)

Would you like to add powerful and easy-to-use Bluetooth Low Energy to your wearable FLORA project? Heck yeah! With BLE now included in modern smart phones and tablets, its fun to add wireless connectivity. So what you really need is the new Adafruit Flora Bluefruit LE!

The Flora Bluefruit LE makes it easy to add Bluetooth Low Energy connectivity to your Flora. Sew 4 traces (or solder 4 wires) and BooM! Bluetooth Low Energy!

![adafruit_products_2487_demo_01A_ORIG.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/368/large1024/adafruit_products_2487_demo_01A_ORIG.jpg?1431373176)

[ Your browser does not support the video tag. ](https://learn.adafruit.com/assets/25362)

For advanced hackers, they'll be very happy to use the standard Nordic UART RX/TX connection profile. In this profile, the Bluefruit acts as a data pipe, that can 'transparently' transmit back and forth from your iOS or Android device. You can use our [iOS App](https://learn.adafruit.com/../../../bluefruit-le-connect-for-ios) or [Android App](https://play.google.com/store/apps/details?id=com.adafruit.bluefruit.le.connect&hl=en), or [write your own to communicate with the UART service](https://learn.adafruit.com/../../../introducing-the-adafruit-bluefruit-le-uart-friend/uart-service).

  * [Can become a BLE Heart Rate Monitor](https://learn.adafruit.com/../../../introducing-the-adafruit-bluefruit-le-uart-friend/heartratemonitor) (a standard profile for BLE) - you just need to add the pulse-detection circuitry
  * [Turn it into a UriBeacon](https://learn.adafruit.com/../../../introducing-the-adafruit-bluefruit-le-uart-friend/uribeacon), the Google standard for Bluetooth LE beacons. Just power it and the 'Friend will bleep out a URL to any nearby devices with the UriBeacon app installed.
  * [Built in over-the-air bootloading capability so we can keep you updated with the hottest new firmware.](https://learn.adafruit.com/../../../introducing-the-adafruit-bluefruit-le-uart-friend/dfu-updates) Use any Android or iOS device to get updates and install them!
![adafruit_products_2487_quarter_ORIG.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/365/large1024/adafruit_products_2487_quarter_ORIG.jpg?1431372796)

[This is the same module and firmware as our BLE UART Friend](https://www.adafruit.com/products/2479) but in a nice rounded shape, so you can switch between the two and have the same working code. This Bluefruit LE does not have the hardware flow control pins so it is best used with a microcontroller with hardware serial support (like, y'know, the Flora!)

![adafruit_products_2487_front_standing_ORIG.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/366/large1024/adafruit_products_2487_front_standing_ORIG.jpg?1431372908)

![adafruit_products_2487_demo_01A_ORIG.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/369/large1024/adafruit_products_2487_demo_01A_ORIG.jpg?1431373229)

![adafruit_products_2487_back_standing_ORIG_01.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/367/large1024/adafruit_products_2487_back_standing_ORIG_01.jpg?1431373077)

On the back we also have a few breakouts!

**Opt. 32 KHz:** If you're doing some funky low power work, [we wanted to give you the option of solderin in a 32khz oscillator. ](https://www.adafruit.com/product/2211)Our firmware doesn't support it _yet_ but its there!

**SWDCLK**: This is the SWD clock pin, 3v logic - for advanced hackers!

**SWDIO**: This is the SWD data pin, 3v logic - for advanced hackers!

**F.RST:** This is the factory reset pin. When all else fails and you did something to really weird out your module, tie this pad to ground while powering up the module and it will factory reset. You should try the DFU reset method first tho (see that tutorial page)

![adafruit_products_2487_demo_01A_ORIG.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/432/large1024/adafruit_products_2487_demo_01A_ORIG.jpg?1431444043)

[ Your browser does not support the video tag. ](https://learn.adafruit.com/assets/25370)

![adafruit_products_BluefruitLE_nrf51_menu.png](https://cdn-learn.adafruit.com/assets/assets/000/025/371/large1024/adafruit_products_BluefruitLE_nrf51_menu.png?1431373421)

> _Upload this sketch and open the Serial Monitor and it should perform a factory reset for you:_

![adafruit_products_Screen_Shot_2015-05-01_at_16.56.17.png](https://cdn-learn.adafruit.com/assets/assets/000/025/372/large1024/adafruit_products_Screen_Shot_2015-05-01_at_16.56.17.png?1431373443)

![adafruit_products_2487_back_standing_ORIG_01.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/374/large1024/adafruit_products_2487_back_standing_ORIG_01.jpg?1431373499)

We're constantly working on the Bluefruit LE firmware to add new features, and keep up to date with what customers need and want.

To make sure you stay up to date with those changes, we've included an easy to use over the air updater on all of our nRF51 based Bluefruit LE modules.

Updating your Bluefruit LE device to the latest firmware is as easy as installing [Adafruit's Bluefruit LE Connect application](https://play.google.com/store/apps/details?id=com.adafruit.bluefruit.le.connect) from the Google Play Store. (An updated iOS version with DFU support will be available shortly!)

Any time a firmware update is available, the application will propose to download the latest binaries and take care of all the details of transferring them to your Bluefruit device, as shown in the video below:

In order to try out our demos, you'll need to download the Adafruit BLE library for the nRF51 based modules such as this one (a.k.a. Adafruit_BluefruitLE_nRF51)

[You can check out the code here at github,](https://github.com/adafruit/Adafruit_BluefruitLE_nRF51) but its likely easier to just download by clicking:

Rename the uncompressed folder **Adafruit_BluefruitLE_nRF51 **and check that the **Adafruit_BluefruitLE_nRF51** folder contains **Adafruit_BLE.****cpp** and **Adafruit_BLE****.h** (as well as a bunch of other files)

Place the **Adafruit_BluefruitLE_nRF51** library folder your **_arduinosketchfolder_/libraries/** folder.   
You may need to create the **libraries** subfolder if its your first library. Restart the IDE.

We also have a great tutorial on Arduino library installation at:  
<http://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use>

After restarting, check that you see the library folder with examples:

![adafruit_products_libraryinstalled.png](https://cdn-learn.adafruit.com/assets/assets/000/025/376/large1024/adafruit_products_libraryinstalled.png?1431373671)

We have tons of examples that will get you going with the Bluefruit, and its really easy! Since we have one library for both wearable and non-wearable Bluefruit's, the example code is the same but may require some minor tweaks to adjust for Flora.

Most importantly, **the flora bluefruit is for use with Hardware Serial only** and does not have flow control pins. Also, **we expect you will not use the mode pad** so you can keep the switch set to CMD and then change into Data mode by sending **+++** .

For all of the examples, look near the top for a line like this:

The **ATCommand** example allows you to execute AT commands from your sketch, and see the results in the Serial Monitor. This can be useful for debugging, or just testing different commands out to see how they work in the real world. It's a good one to start with!

![adafruit_products_Screen_Shot_2015-04-30_at_23.10.01.png](https://cdn-learn.adafruit.com/assets/assets/000/025/091/large1024/adafruit_products_Screen_Shot_2015-04-30_at_23.10.01.png?1430428297)

> _This will open up a new instance of the example in the IDE, as shown below:_

![adafruit_products_atcomm.png](https://cdn-learn.adafruit.com/assets/assets/000/025/475/large1024/adafruit_products_atcomm.png?1431541699)

Check the **Configuration!** page earlier to set up the sketch for Software/Hardware UART or Software/Hardware SPI. The default is hardware SPI

  * This tutorial does not need to use the MODE pin, **make sure you have the mode switch in CMD mode ** if you do not configure & connect a MODE pin
  * Don't forget to also** connect the CTS pin on the Bluefruit to ground if you are not using it!** (The Flora has this already done)
![adafruit_products_atcomman.png](https://cdn-learn.adafruit.com/assets/assets/000/025/477/large1024/adafruit_products_atcomman.png?1431542525)

To send an AT command to the Bluefruit LE module, enter the command in the textbox at the top of the Serial Monitor and click the **Send** button:

![adafruit_products_Screen_Shot_2015-04-30_at_23.20.46.png](https://cdn-learn.adafruit.com/assets/assets/000/025/096/large1024/adafruit_products_Screen_Shot_2015-04-30_at_23.20.46.png?1430428897)

![adafruit_products_Screen_Shot_2015-04-30_at_23.22.33.png](https://cdn-learn.adafruit.com/assets/assets/000/025/097/large1024/adafruit_products_Screen_Shot_2015-04-30_at_23.22.33.png?1430428968)

You can do pretty much anything at this prompt, with the AT command set. Try **AT+HELP **to get a list of all commands, and try out ones like** AT+HWGETDIETEMP** (get temperature at the nRF51822 die) and **AT+HWRANDOM** (generate a random number)

![adafruit_products_othercomm.png](https://cdn-learn.adafruit.com/assets/assets/000/025/478/large1024/adafruit_products_othercomm.png?1431542699)

The **BLEUart** example sketch allows you to send and receive text data between the Arduino and a connected Bluetooth Low Energy Central device on the other end (such as you mobile phone using the **Adafruit Bluefruit LE Connect** application for [Android](https://play.google.com/store/apps/details?id=com.adafruit.bluefruit.le.connect) or [iOS](https://itunes.apple.com/app/adafruit-bluefruit-le-connect/id830125974?mt=8) in UART mode).

![adafruit_products_BluefruitLE_nrf51_menu.png](https://cdn-learn.adafruit.com/assets/assets/000/025/099/large1024/adafruit_products_BluefruitLE_nrf51_menu.png?1430429200)

> _This will open up a new instance of the example in the IDE, as shown below:_

![adafruit_products_uartcmdsketch.png](https://cdn-learn.adafruit.com/assets/assets/000/025/479/large1024/adafruit_products_uartcmdsketch.png?1431543315)

Check the **Configuration!** page earlier to set up the sketch for Software/Hardware UART or Software/Hardware SPI. The default is hardware SPI

  * This tutorial does not need to use the MODE pin, **make sure you have the mode switch in CMD mode ** if you do not configure & connect a MODE pin
  * Don't forget to also** connect the CTS pin on the Bluefruit to ground if you are not using it!** (The Flora has this already done)
![adafruit_products_uartconn.png](https://cdn-learn.adafruit.com/assets/assets/000/025/480/large1024/adafruit_products_uartconn.png?1431543645)

![adafruit_products_conn.png](https://cdn-learn.adafruit.com/assets/assets/000/025/481/large1024/adafruit_products_conn.png?1431543828)

![adafruit_products_IMG_0061.png](https://cdn-learn.adafruit.com/assets/assets/000/025/103/large1024/adafruit_products_IMG_0061.png?1430430143)

> _The response text ('Why hello, Arduino!') can be seen below:_

![adafruit_products_rply.png](https://cdn-learn.adafruit.com/assets/assets/000/025/482/large1024/adafruit_products_rply.png?1431543860)

![adafruit_products_ControllerMenu.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/487/large1024/adafruit_products_ControllerMenu.jpg?1431547644)

> _This will open up a new instance of the example in the IDE, as shown below:_

![adafruit_products_Screen_Shot_2015-05-13_at_22.07.56.png](https://cdn-learn.adafruit.com/assets/assets/000/025/488/large1024/adafruit_products_Screen_Shot_2015-05-13_at_22.07.56.png?1431547696)

Check the Configuration! page earlier to set up the sketch for Software/Hardware UART or Software/Hardware SPI. The default is hardware SPI

**If using software or hardware Serial UART:**

  * This tutorial will also be easier to use if you wire up the MODE pin, you can use any pin but our tutorial has pin 12 by default. You can change this to any pin. If you do not set the MODE pin then **make sure you have the mode switch in CMD** mode
  * If you are using a Flora or otherwise don't want to wire up the Mode pin, set the BLUEFRUIT_UART_MODE_PIN to -1 in the configuration tab so that the sketch will use the +++ method to switch between Command and Data mode!
  * Don't forget to also** connect the CTS pin on the Bluefruit to ground if you are not using it!** (The Flora has this already done)
![adafruit_products_Screen_Shot_2015-05-13_at_22.20.12.png](https://cdn-learn.adafruit.com/assets/assets/000/025/490/large1024/adafruit_products_Screen_Shot_2015-05-13_at_22.20.12.png?1431548426)

> _Using Bluefruit LE Connect in Controller Mode_

On the welcome screen, select the **Adafruit Bluefruit LE** device from the list of BLE devices in range:

![adafruit_products_BluefruitLEIcon.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/492/large1024/adafruit_products_BluefruitLEIcon.jpg?1431548912)

> _Then from the activity list select Controller:_

![adafruit_products_Activities.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/493/large1024/adafruit_products_Activities.jpg?1431548962)

> _This will bring up a list of data points you can send from your phone or tablet to your Bluefruit LE module, by enabling or disabling the appropriate sensor(s)._

![adafruit_products_Accelerometer.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/494/large1024/adafruit_products_Accelerometer.jpg?1431549087)

> _The data is parsed in the example sketch and output to the Serial Monitor as follows:_

![adafruit_products_Screen_Shot_2015-05-13_at_22.21.17.png](https://cdn-learn.adafruit.com/assets/assets/000/025/495/large1024/adafruit_products_Screen_Shot_2015-05-13_at_22.21.17.png?1431549146)

![adafruit_products_ControlPad.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/496/large1024/adafruit_products_ControlPad.jpg?1431549378)

> _This will bring up the Control Pad panel, shown below:_

![adafruit_products_IMG_0080.png](https://cdn-learn.adafruit.com/assets/assets/000/025/497/large1024/adafruit_products_IMG_0080.png?1431549452)

> _Button presses and releases will all be logged to the Serial Monitor with the ID of the button used:_

![adafruit_products_ColorPicker.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/499/large1024/adafruit_products_ColorPicker.jpg?1431549751)

> _This will give you Hexadecimal color data in the following format:_

**HIDKeyboard** example shows you how you can use the built-in HID keyboard AT commands to send keyboard data to any BLE-enabled Android or iOS phone, or other device that supports BLE HID peripherals.

![adafruit_products_BluefruitLE_nrf51_menu.png](https://cdn-learn.adafruit.com/assets/assets/000/025/107/large1024/adafruit_products_BluefruitLE_nrf51_menu.png?1430441050)

> _This will open up a new instance of the example in the IDE, as shown below:_

![adafruit_products_hidkey.png](https://cdn-learn.adafruit.com/assets/assets/000/025/142/large1024/adafruit_products_hidkey.png?1430506317)

Check the **Configuration!** page earlier to set up the sketch for Software/Hardware UART or Software/Hardware SPI. The default is hardware SPI

  * This tutorial does not need to use the MODE pin, **make sure you have the mode switch in CMD mode!**
  * Don't forget to also** connect the CTS pin on the Bluefruit to ground if you are not using it!** (The Flora has this already done)
![adafruit_products_hidkey.png](https://cdn-learn.adafruit.com/assets/assets/000/025/485/large1024/adafruit_products_hidkey.png?1431545669)

![adafruit_products_Android_BLEBond_1.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/119/large1024/adafruit_products_Android_BLEBond_1.jpg?1430486303)

Inside the Bluetooth setting panel you should see the Bluefruit LE module advertising itself as **Bluefruit Keyboard** under the 'Available devices' list:

![adafruit_products_Android_BLEBond_2.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/120/large1024/adafruit_products_Android_BLEBond_2.jpg?1430486364)

![adafruit_products_Android_BLEBond_3.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/121/large1024/adafruit_products_Android_BLEBond_3.jpg?1430486502)

> _To delete the bonding information, click the gear icon to the right of the device name and the click the Forget button:_

![adafruit_products_Android_BLEBond_4.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/122/large1024/adafruit_products_Android_BLEBond_4.jpg?1430486641)

![adafruit_products_iOS_Bluetooth_1.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/123/large1024/adafruit_products_iOS_Bluetooth_1.jpg?1430488149)

Once the bonding process is complete the device will be moved to the **MY DEVICES** category, and you can start to use the Bluefruit LE module as a keyboard:

![adafruit_products_iOS_Bluetooth_2.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/124/large1024/adafruit_products_iOS_Bluetooth_2.jpg?1430488310)

> _To unbond the device, click the 'info' icon and then select the Forget this Device option in the menu:_

![adafruit_products_iOS_Bluetooth_3.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/125/large1024/adafruit_products_iOS_Bluetooth_3.jpg?1430488401)

![adafruit_products_Screen_Shot_2015-05-01_at_15.07.13.png](https://cdn-learn.adafruit.com/assets/assets/000/025/118/large1024/adafruit_products_Screen_Shot_2015-05-01_at_15.07.13.png?1430485675)

> _To unbond the device once it has been paired, click the small 'x' icon beside Bluefruit Keyboard:_

![adafruit_products_Screen_Shot_2015-05-01_at_15.55.06.png](https://cdn-learn.adafruit.com/assets/assets/000/025/126/large1024/adafruit_products_Screen_Shot_2015-05-01_at_15.55.06.png?1430488573)

> _... and then click the Remove button when the confirmation dialogue box pops up:_

![adafruit_products_Screen_Shot_2015-05-01_at_15.55.13.png](https://cdn-learn.adafruit.com/assets/assets/000/025/127/large1024/adafruit_products_Screen_Shot_2015-05-01_at_15.55.13.png?1430488633)

The **UriBeacon** example shows you how to use the built-in UriBeacon AT commands to configure the Bluefruit LE module as a UriBeacon advertiser, following Google's Physical Web [UriBeacon](https://github.com/google/uribeacon) specification.

![adafruit_products_BluefruitLE_nrf51_menu.png](https://cdn-learn.adafruit.com/assets/assets/000/025/109/large1024/adafruit_products_BluefruitLE_nrf51_menu.png?1430441108)

This will open up a new instance of the example in the IDE, as shown below. You can edit the URL that the beacon will point to, from the default **http://www.adafruit.com** or just upload as is to test

![adafruit_products_uribeacon.png](https://cdn-learn.adafruit.com/assets/assets/000/025/141/large1024/adafruit_products_uribeacon.png?1430506173)

Check the **Configuration!** page earlier to set up the sketch for Software/Hardware UART or Software/Hardware SPI. The default is hardware SPI

  * This tutorial does not need to use the MODE pin, **make sure you have the mode switch in CMD mode ** if you do not configure & connect a MODE pin
  * Don't forget to also** connect the CTS pin on the Bluefruit to ground if you are not using it!** (The Flora has this already done)
![adafruit_products_urib.png](https://cdn-learn.adafruit.com/assets/assets/000/025/486/large1024/adafruit_products_urib.png?1431546147)

At this point you can open the Physical Web Application for [Android](https://play.google.com/store/apps/details?id=physical_web.org.physicalweb) or for [iOS](https://itunes.apple.com/us/app/physical-web/id927653608?mt=8), and you should see a link advertising Adafruit's website:

![adafruit_products_UriBeacon.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/131/large1024/adafruit_products_UriBeacon.jpg?1430491397)

![adafruit_products_BluefruitLE_nrf51_menu.png](https://cdn-learn.adafruit.com/assets/assets/000/025/106/large1024/adafruit_products_BluefruitLE_nrf51_menu.png?1430441010)

> _This will open up a new instance of the example in the IDE, as shown below:_

![adafruit_products_hrm.png](https://cdn-learn.adafruit.com/assets/assets/000/025/143/large1024/adafruit_products_hrm.png?1430506404)

This tutorial does not need to use the MODE pin, **make sure you have the mode switch in CMD mode ** if you do not configure & connect a MODE pin

This demo uses some long data transfer strings, so we recommend defining and connecting both CTS and RTS to pins, even if you are using hardware serial.

If you are using a Flora or just dont want to connect CTS or RTS, set the pin #define's to -1 and **Don't forget to also connect the CTS pin on the Bluefruit to ground!** (The Flora has this already done)

If you are using RTS and CTS, you can remove this line below, which will slow down the data transmission

![adafruit_products_hrm1.png](https://cdn-learn.adafruit.com/assets/assets/000/025/483/large1024/adafruit_products_hrm1.png?1431545409)

![adafruit_products_hrm2.png](https://cdn-learn.adafruit.com/assets/assets/000/025/484/large1024/adafruit_products_hrm2.png?1431545456)

If you open up an application on your mobile device or laptop that support the standard [Heart Rate Monitor Service](https://developer.bluetooth.org/TechnologyOverview/Pages/HRS.aspx), you should be able to see the heart rate being updated in sync with the changes seen in the Serial Monitor:

![adafruit_products_Screenshot_2015-05-01-03-12-18.png](https://cdn-learn.adafruit.com/assets/assets/000/025/116/large1024/adafruit_products_Screenshot_2015-05-01-03-12-18.png?1430443100)

> _CoreBluetooth HRM Example_

![adafruit_products_Screen_Shot_2015-05-01_at_03.04.36.png](https://cdn-learn.adafruit.com/assets/assets/000/025/115/large1024/adafruit_products_Screen_Shot_2015-05-01_at_03.04.36.png?1430442438)

![adafruit_products_couldntfind.png](https://cdn-learn.adafruit.com/assets/assets/000/025/476/large1024/adafruit_products_couldntfind.png?1431542393)

For UART/Serial Bluefruits:

  * Check you have the **MODE** switch in CMD and the MODE pin not wired to anything if it isnt used!
  * If you are trying to control the **MODE** from your micro, make sure you set the MODE pin in the sketch
  * Make sure you have **RXI** and **TXO** wired right! They are often swapped by accident
  * Make sure **CTS** is tied to GND if you are using hardware serial and not using CTS
  * Check the MODE red LED, is it blinking? If its blinking continuously, you might be in DFU mode, power cycle the module!
  * If you are using Hardware Serial/Software Serial make sure you know which one and have that set up

If using SPI Bluefruit:

  * Make sure you have all 5 (or 6) wires connected properly.
  * If using hardware SPI, you need to make sure you're connected to the hardware SPI port, which differs depending on the main chipset.

If using Bluefruit Micro:

  * Make sure you change the **RESET** pin to #4 in any Config file. Also be sure you are using hardware SPI to connect!

By placing the Flora BLEFriend module in 'UART Data' mode (set the mode selection switch to **DATA **or setting the MODE pin to gound) you can use the module as a 'tranparent UART connection' to the Bluefruit app. This makes data transfer super simple. Data is sent to the app when any 9600 baud data is received on the **RX **pin and any data from the app is automatically transmitted via the **TX** pin to your Flora

[ Your browser does not support the video tag. ](https://learn.adafruit.com/assets/25430)

![adafruit_products_IMG_0061.png](https://cdn-learn.adafruit.com/assets/assets/000/025/379/large1024/adafruit_products_IMG_0061.png?1431373941)
    
          1. > Hello, World! Data mode!

[ Your browser does not support the video tag. ](https://learn.adafruit.com/assets/25426)

When operating in command mode, the Bluefruit LE Pro modules use a [Hayes AT-style command set ](http://en.wikipedia.org/wiki/Hayes_command_set)to configure the device.

The advantage of an AT style command set is that it's easy to use in machine to machine communication, while still being somewhat user friendly for humans.

[We have a huge amount of commands and details on how to use them, so please do check out our list of possible commands over on the Bluefruit LE page](https://learn.adafruit.com/../../../../introducing-the-adafruit-bluefruit-le-uart-friend/command-mode-1) (no need to duplicate all of the content here!)

![adafruit_products_schem.png](https://cdn-learn.adafruit.com/assets/assets/000/025/434/large1024/adafruit_products_schem.png?1431444297)

> _Fabrication print_

![adafruit_products_bleprint.png](https://cdn-learn.adafruit.com/assets/assets/000/025/435/large1024/adafruit_products_bleprint.png?1431444316)
