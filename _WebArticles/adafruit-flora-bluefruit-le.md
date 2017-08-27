# Adafruit Flora Bluefruit LE

_Captured: 2017-08-24 at 23:45 from [learn.adafruit.com](https://learn.adafruit.com/adafruit-flora-bluefruit-le?view=all)_

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

![adafruit_products_2487_demo_01A_ORIG.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/432/large1024/adafruit_products_2487_demo_01A_ORIG.jpg?1431444043)

![adafruit_products_BluefruitLE_nrf51_menu.png](https://cdn-learn.adafruit.com/assets/assets/000/025/371/large1024/adafruit_products_BluefruitLE_nrf51_menu.png?1431373421)

> _Upload this sketch and open the Serial Monitor and it should perform a factory reset for you:_

![adafruit_products_Screen_Shot_2015-05-01_at_16.56.17.png](https://cdn-learn.adafruit.com/assets/assets/000/025/372/large1024/adafruit_products_Screen_Shot_2015-05-01_at_16.56.17.png?1431373443)

![adafruit_products_2487_back_standing_ORIG_01.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/374/large1024/adafruit_products_2487_back_standing_ORIG_01.jpg?1431373499)

![adafruit_products_libraryinstalled.png](https://cdn-learn.adafruit.com/assets/assets/000/025/376/large1024/adafruit_products_libraryinstalled.png?1431373671)

![adafruit_products_atcomm.png](https://cdn-learn.adafruit.com/assets/assets/000/025/475/large1024/adafruit_products_atcomm.png?1431541699)

![adafruit_products_atcomman.png](https://cdn-learn.adafruit.com/assets/assets/000/025/477/large1024/adafruit_products_atcomman.png?1431542525)

![adafruit_products_Screen_Shot_2015-04-30_at_23.22.33.png](https://cdn-learn.adafruit.com/assets/assets/000/025/097/large1024/adafruit_products_Screen_Shot_2015-04-30_at_23.22.33.png?1430428968)

![adafruit_products_uartcmdsketch.png](https://cdn-learn.adafruit.com/assets/assets/000/025/479/large1024/adafruit_products_uartcmdsketch.png?1431543315)

![adafruit_products_Screen_Shot_2015-05-13_at_22.07.56.png](https://cdn-learn.adafruit.com/assets/assets/000/025/488/large1024/adafruit_products_Screen_Shot_2015-05-13_at_22.07.56.png?1431547696)

![adafruit_products_Screen_Shot_2015-05-13_at_22.20.12.png](https://cdn-learn.adafruit.com/assets/assets/000/025/490/large1024/adafruit_products_Screen_Shot_2015-05-13_at_22.20.12.png?1431548426)

> _Using Bluefruit LE Connect in Controller Mode_

![adafruit_products_Activities.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/493/large1024/adafruit_products_Activities.jpg?1431548962)

> _This will bring up a list of data points you can send from your phone or tablet to your Bluefruit LE module, by enabling or disabling the appropriate sensor(s)._

![adafruit_products_Accelerometer.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/494/large1024/adafruit_products_Accelerometer.jpg?1431549087)

> _The data is parsed in the example sketch and output to the Serial Monitor as follows:_

![adafruit_products_Screen_Shot_2015-05-13_at_22.21.17.png](https://cdn-learn.adafruit.com/assets/assets/000/025/495/large1024/adafruit_products_Screen_Shot_2015-05-13_at_22.21.17.png?1431549146)

![adafruit_products_hidkey.png](https://cdn-learn.adafruit.com/assets/assets/000/025/142/large1024/adafruit_products_hidkey.png?1430506317)

![adafruit_products_Android_BLEBond_4.jpg](https://cdn-learn.adafruit.com/assets/assets/000/025/122/large1024/adafruit_products_Android_BLEBond_4.jpg?1430486641)
