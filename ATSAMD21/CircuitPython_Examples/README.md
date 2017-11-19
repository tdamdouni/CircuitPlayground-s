## CircuitPython Examples
General example code for using the different hardware components on Adafruit's Circuit Playground Express (CPX).

Some of these examples require a CircuitPython package from [Adafruit's github site](https://github.com/adafruit). Check the comments of each sample for specific package locations.

To use these examples you must be running CircuitPython on your board. [Download the latest CP release from Adafruit](https://github.com/adafruit/circuitpython/releases). Once you have CP running, copy the example code to your CPX and rename the file main.py.

### Examples

- [accelerometer.py](accelerometer.py)  
Demonstrates the use of the lis3dh with a simple "level" program.

- [buttons.py](buttons.py)  
Demonstrates the use of buttons to drive conditional statements.

- [max_light_reading.py](max_light_reading.py)  
Demonstrates the use of the photoresistor to read light values.

- [neopixel_scan.py](neopixel_scan.py)  
Demonstrates the use of neopixels with a simple Cylon / KITT animation

- [speaker_play_wav.py](speaker/speaker_play_wav.py)  
Demonstrates using the speaker to play a sound file.

- [switch.py](switch.py)  
Demonstrates the use of the slide switch in conditional statements.

- [thermistor.py](thermistor.py)  
Demonstrates the use of thermistor with a simple temperature gauge.

### Howto CircuitPython REPL

The REPL (Read-Eval-Print-Loop) that comes as part of the CircuitPython installation can be thought of as an interactive shell for CircuitPython. It's useful for seeing board output (e.g. print statements) and for issuing commands directly to the board.

These instructions are for Mac users though the connection should be similar for other platforms.

#### To Connect to the CPX REPL

1.  Start Terminal
2.  Connect your CPX to USB on your computer
3.  Enter the following command.
      ls /dev/tty.usb*
4.  Identify the USB port the CPX is connected to
5.  Enter the following command.
      screen /dev/<CPX USB PORT> 115200
      (e.g. screen /dev/tty.usbmodem1431 115200)
6.  You should see the command prompt >>> (if not, try pressing ctrl-c)

#### Using the REPL to View Program Output

1.  Connect to the REPL (above)
2.  Press ctrl-d to enter console mode and restart the program on your CPX
3.  Your program should run from the beginning and any output (print() statements) should print here.

#### Using the REPL in Interactive mode

1.  Connect to the REPL (above)
2.  Press ctrl-c to break out of any running programs and enter interactive mode.
3.  At the prompt '>>>' enter the CircuitPython commands. *Note: functions, loops, and conditional statements can be entered on multiple lines. To enter the multiline edit mode just starting typing your multi-line command ending with ':'. Once you've completed the code block move cursor to start of blank line and hit enter twice. Loops and conditional statements will execute immediately. functions are defined and can be called using their names.*
