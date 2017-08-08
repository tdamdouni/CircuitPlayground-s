# Overview

_Captured: 2017-08-06 at 20:43 from [learn.adafruit.com](https://learn.adafruit.com/circuit-playground-hourglass?view=all)_

In this guide we'll go through the steps to create an hourglass style timer with your Circuit Playground.

An [hourglass](https://en.wikipedia.org/wiki/Hourglass) is an ancient timing device used to measure a fixed amount of time. It contains two chambers separated by a thin neck that allows sand to pass from one chamber to the other very slowly. The overall size and amount of sand determines the amount of time. Once all the sand has emptied into one side, the hourglass is simply inverted to start counting time again.

Here, we'll use the NeoPixels on the Circuit Playground to represent the grains of sand in an hourglass, having them "disappear" one at a time by turning them off. We can even have the hourglass "reset" by turning the Circuit Playground over. We'll build this up one step at a time and walk through each one.

  * ![circuit_playground_items.jpg](https://cdn-learn.adafruit.com/assets/assets/000/037/791/medium640/circuit_playground_items.jpg?1480993072)

  * 3 x AAA Batteries (NiMH work great!)

If you are new to the Circuit Playground, you may want to first read these overview guides.

This project will use the Arduino IDE. Make sure you have added the board support for the Circuit Playground as well as installed the Circuit Playground library. **MUST DO BOTH. **This is covered in the guides linked above.

An hourglass does one thing, count a fixed period time. We can do the same thing very easily with the Circuit Playground using the `delay()` function from the [core Arduino library](https://www.arduino.cc/en/Reference/Delay). This function simply takes an amount of time, in milliseconds, and waits that amount of time.

So we can make a basic timer by turning on all of the NeoPixels, waiting the specified amount of time using `delay()`, and then turning off all of the NeoPixels to indicate the time has elapsed.

Easy peasy lemony squeezy, here's the code to do that:
    
          1. ///////////////////////////////////////////////////////////////////////////////
      2. // MIT License (https://opensource.org/licenses/MIT)
      3. ///////////////////////////////////////////////////////////////////////////////
      4. void setup() {
      5. ///////////////////////////////////////////////////////////////////////////////
      6. for (int p=0; p<10; p++) {
      7. CircuitPlayground.setPixelColor(p, 255, 255, 255);
      8. while (!CircuitPlayground.leftButton()   &&
      9. !CircuitPlayground.rightButton())  {

In the code above, the timer was hard coded for 5 seconds. Since there are 1000 milliseconds in a second, we need to multiply 5 by 1000 to get the value for `delay()`.

**5 seconds X 1000 milliseconds/second = 5000 milliseconds**

In a real hourglass, the sands fall through slowly, not all at once. So next we'll look at how to turn off the NeoPixels one a time to simulate the grains of sand.

Now let's see how to turn off the NeoPixels one at a time during the count time. The basic idea is shown in the figure below.

![circuit_playground_time_line.png](https://cdn-learn.adafruit.com/assets/assets/000/037/792/large1024/circuit_playground_time_line.png?1480994244)

Our timer starts at time zero (t=0) and counts for a total amount of time **T** (t=T). Since we have 10 NeoPixels on the Circuit Playground, we can break that time period up in to 10 equal slices. Each slice has a wait time of **DT**, which is equal to the total time **T**, divide by the number of NeoPixels, thus:

**DT = T / 10**

The idea now is to loop over each NeoPixel and wait this smaller amount of time **DT**. Once that time has elapsed, turn the NeoPixel off and move on to the next NeoPixel, etc.

Here's the previous code modified to do this:
    
          1. ///////////////////////////////////////////////////////////////////////////////
      2. ///////////////////////////////////////////////////////////////////////////////
      3. for (int p=0; p<10; p++) {
      4. CircuitPlayground.setPixelColor(p, 255, 255, 255);
      5. unsigned long DT = 5000/10;
      6. for (int p=0; p<10; p++) {
      7. CircuitPlayground.setPixelColor(p, 0, 0, 0);
      8. while (!CircuitPlayground.leftButton()   &&
      9. !CircuitPlayground.rightButton())  {

As you can see, the `delay()` command has been moved inside a loop. The loop runs 10 times, so the `delay()` command gets called 10 times. However, the total amount of time counted remains the same 5 seconds as before.

Hourglasses typically don't have buttons that are pressed to reset them like our Circuit Playground code is doing. An hourglass is reset by simply flipping it over and letting the sand run through in the other direction. How can we simulate this action with the Circuit Playground? Well, maybe we can use the accelerometer. Let's give that a try.

To make things easy, let's assume the hourglass timer will be used with the Circuit Playground facing up. The NeoPixels are on that side, so this makes sense. It also let's us use the Z axis of the accelerometer to detect when the Circuit Playground is flipped over. If you want more info on the accelerometer, see the [this guide](https://learn.adafruit.com/../../../../how-tall-is-it/hello-accelerometer).

The figure below shows a time history of the value returned from `CircuitPlayground.motionZ()` with the Circuit Playground facing up and down.

![circuit_playground_accelo_time_hist.png](https://cdn-learn.adafruit.com/assets/assets/000/037/793/large1024/circuit_playground_accelo_time_hist.png?1480995359)

The value of 9.8 m/s2 relates to earth gravity. With the Circuit Playground facing up, it is a positive value. With the Circuit Playground facing down, it is a negative value. So we can detect a flip by simply checking the sign of the value.

We start with the Circuit Playground face up and a positive value. The first step is to wait for the value to become negative. Then, once it is negative, we wait for it to become positive again. That's a flip!

Here's a simple sketch that demonstrates this logic being used to detect a flip and then play a tone.
    
          1. void setup() {
      2. while (CircuitPlayground.motionZ() > 0) {};
      3. while (CircuitPlayground.motionZ() < 0) {};
      4. CircuitPlayground.playTone(800,1000);

The little lines of code that look like:

are called "parking loops". If we wanted them to actually do something, we would place that code in the `{}` brackets. In this case all we want to do is wait until the condition being tested becomes true. So the program execution just "parks" here until that happens.

The line of code with the small delay:

is needed to prevent false flip detection. This can occur as the processor runs fast enough that it might see a brief positive value immediately after the first negative value, due to noise or small amounts of real motion. By waiting a small amount of time before checking the accelerometer value again, we prevent this.
    
          1. ///////////////////////////////////////////////////////////////////////////////
      2. void setup() {
      3. ///////////////////////////////////////////////////////////////////////////////
      4. for (int p=0; p<10; p++) {
      5. CircuitPlayground.setPixelColor(p, 255, 255, 255);
      6. unsigned long DT = 5000/10;
      7. for (int p=0; p<10; p++) {
      8. CircuitPlayground.setPixelColor(p, 0, 0, 0);
      9. while (CircuitPlayground.motionZ() > 0) {};
      10. while (CircuitPlayground.motionZ() < 0) {};

So at this point we have a basic working hourglass. It counts for a period of 5 seconds, turning off the NeoPixels one at a time, and can be reset by flipping the Circuit Playground over.

If you want to set the timer to a different amount of time, simply change this line of code:

and replace 5000 with whatever value you want. However, a better way to do this is to define this value globally at the top of the code. Try this - first, modify the code by adding a **#define** statement near the top as shown below.

Now change the line that computes **DT** as follows:

Run this and watch what happens when the count gets to the end. It works fine, but since the total time (**COUNT_TIME**) is now longer, so is the delay (**DT**) at each NeoPixel. This makes it difficult to see the last bit of time elapsing. The last NeoPixel is on, then suddenly off.

So how can we indicate the time progress for each NeoPixel? How about fading them? That might work, let's give it a try.

Our previous code simply waited at each NeoPixel the computed amount of time** DT**, and then turned the NeoPixel off. Now let's change things so that the NeoPixel fades out over this period of time.

Basically, we need to go one level deeper on our time line. Now, within each time slice **DT**, instead of doing nothing, we'll be fading the NeoPixel. See the figure below.

![circuit_playground_fading_time_line.png](https://cdn-learn.adafruit.com/assets/assets/000/037/829/large1024/circuit_playground_fading_time_line.png?1481053563)

The value **N** is just an arbitrary number of steps over which the fading will occur. This further divides the time slice **DT** into smaller slices, called **FADE_DT** in the figure above.

The simplest way to fade a NeoPixel is to linearly change the setting from its starting value down to zero. The NeoPixels on the Circuit Playground have red, green, and blue LEDs in them, so we do the same thing for each of the color components individually. This idea is shown in the figure below.

![circuit_playground_fading_time_line2.png](https://cdn-learn.adafruit.com/assets/assets/000/037/830/large1024/circuit_playground_fading_time_line2.png?1481053581)

So at each of the fading time steps, we decrease the red, green, and blue values by a small amount. After doing this **N** times, the values will reach 0.

OK, here's our final code, with flip-to-reset and fading NeoPixel grains of sand.
    
          1. float r, g, b;
      2. float dr, dg, db;
      3. ///////////////////////////////////////////////////////////////////////////////
      4. Serial.begin(9600);
      5.   DT = COUNT_TIME / 10;
      6.   dr = float(R_SAND) / float(FADE_STEPS);
      7.   dg = float(G_SAND) / float(FADE_STEPS);
      8.   db = float(B_SAND) / float(FADE_STEPS);
      9. ///////////////////////////////////////////////////////////////////////////////
      10. for (int p=0; p<10; p++) {
      11. CircuitPlayground.setPixelColor(p, uint8_t(R_SAND),
      12. uint8_t(G_SAND),
      13. uint8_t(B_SAND));
      14. for (int p=0; p<10; p++) {
      15.     r = float(R_SAND);
      16.     g = float(G_SAND);
      17.     b = float(B_SAND);
      18. for (int n=0; n<FADE_STEPS; n++) {
      19.       delay(DT/FADE_STEPS); // Per fade step delay
      20.       r = r - dr;           // Decrease the red value
      21.       g = g - dg;           //    "      "  green "
      22.       b = b - db;           //    "      "  blue  "
      23. CircuitPlayground.setPixelColor(p, uint8_t(r),
      24. uint8_t(g),
      25. uint8_t(b));
      26. while (CircuitPlayground.motionZ() > 0) {};
      27. while (CircuitPlayground.motionZ() < 0) {};

The following are some questions related to this project along with some suggested code challenges. The idea is to provoke thought, test your understanding, and get you coding!

While the sketches provided in this guide work, there is room for improvement and additional features. Have fun playing with the provided code to see what you can do with it.

# [Circuit Playground Hourglass](/circuit-playground-hourglass/overview)

[Like sands through the hourglass, so are the 1s and 0s of your Circuit Playground.](/circuit-playground-hourglass/overview)

  * Overview
  * Basic Timer
  * Less Basic Timer
  * Flip Detect
  * Basic Hourglass
  * Fading Hourglass
  * Questions and Code Challenges
  *   * [Multiple Pages](/circuit-playground-hourglass)
  * [Download PDF](https://cdn-learn.adafruit.com/downloads/pdf/circuit-playground-hourglass.pdf)

#### Contributors

[Carter Nelson](/users/caternuson)

[ Feedback? Corrections? ](/pages/8572/settings_modal)

[CIRCUIT PLAYGROUND](/category/circuit-playground) [ __ ](/guides/1529/favorites.js)

#  Overview

by [ Carter Nelson ](/users/caternuson)

In this guide we'll go through the steps to create an hourglass style timer with your Circuit Playground.

An [hourglass](https://en.wikipedia.org/wiki/Hourglass) is an ancient timing device used to measure a fixed amount of time. It contains two chambers separated by a thin neck that allows sand to pass from one chamber to the other very slowly. The overall size and amount of sand determines the amount of time. Once all the sand has emptied into one side, the hourglass is simply inverted to start counting time again.

Here, we'll use the NeoPixels on the Circuit Playground to represent the grains of sand in an hourglass, having them "disappear" one at a time by turning them off. We can even have the hourglass "reset" by turning the Circuit Playground over. We'll build this up one step at a time and walk through each one.

#  Required Parts

This project uses the sensors already included on the Circuit Playground. The only additional items needed are batteries for power and a holder for the batteries.

  * [ ![circuit_playground_items.jpg](https://cdn-learn.adafruit.com/assets/assets/000/037/791/medium640/circuit_playground_items.jpg?1480993072) ](/assets/37791)
  * [Circuit Playground](https://www.adafruit.com/products/3000)
  * [3 x AAA Battery Holder](https://www.adafruit.com/products/727)
  * 3 x AAA Batteries (NiMH work great!)

#  Before Starting

If you are new to the Circuit Playground, you may want to first read these overview guides.

  * [Overview](../../../../introducing-circuit-playground)
  * [Lesson #0](../../../../circuit-playground-lesson-number-0)

This project will use the Arduino IDE. Make sure you have added the board support for the Circuit Playground as well as installed the Circuit Playground library. **MUST DO BOTH. **This is covered in the guides linked above.

#  Basic Timer

by [ Carter Nelson ](/users/caternuson)

An hourglass does one thing, count a fixed period time. We can do the same thing very easily with the Circuit Playground using the `delay()` function from the [core Arduino library](https://www.arduino.cc/en/Reference/Delay). This function simply takes an amount of time, in milliseconds, and waits that amount of time.

__ 1 second = 1000 milliseconds 

So we can make a basic timer by turning on all of the NeoPixels, waiting the specified amount of time using `delay()`, and then turning off all of the NeoPixels to indicate the time has elapsed.

Easy peasy lemony squeezy, here's the code to do that:

Copy Code

    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Basic Timer
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Turn ON all the NeoPixels
      for (int p=0; p<10; p++) {
        CircuitPlayground.setPixelColor(p, 255, 255, 255);
      }
    
      // Wait 5 seconds (5000 milliseconds)
      delay(5000);
    
      // Turn OFF all the NeoPixels
      CircuitPlayground.clearPixels();
    
      // Wait for button press to reset timer
      while (!CircuitPlayground.leftButton()   && 
             !CircuitPlayground.rightButton())  {
        // Do nothing, just waiting for a button press...
      }
    }
    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Basic Timer
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Turn ON all the NeoPixels
      for (int p=0; p<10; p++) {
        CircuitPlayground.setPixelColor(p, 255, 255, 255);
      }
    
      // Wait 5 seconds (5000 milliseconds)
      delay(5000);
    
      // Turn OFF all the NeoPixels
      CircuitPlayground.clearPixels();
    
      // Wait for button press to reset timer
      while (!CircuitPlayground.leftButton()   && 
             !CircuitPlayground.rightButton())  {
        // Do nothing, just waiting for a button press...
      }
    }

In the code above, the timer was hard coded for 5 seconds. Since there are 1000 milliseconds in a second, we need to multiply 5 by 1000 to get the value for `delay()`.

**5 seconds X 1000 milliseconds/second = 5000 milliseconds**

#  Next

In a real hourglass, the sands fall through slowly, not all at once. So next we'll look at how to turn off the NeoPixels one a time to simulate the grains of sand.

#  Less Basic Timer

by [ Carter Nelson ](/users/caternuson)

Now let's see how to turn off the NeoPixels one at a time during the count time. The basic idea is shown in the figure below.

[ ![circuit_playground_time_line.png](https://cdn-learn.adafruit.com/assets/assets/000/037/792/medium800/circuit_playground_time_line.png?1480994244) __ ](/assets/37792)

Our timer starts at time zero (t=0) and counts for a total amount of time **T** (t=T). Since we have 10 NeoPixels on the Circuit Playground, we can break that time period up in to 10 equal slices. Each slice has a wait time of **DT**, which is equal to the total time **T**, divide by the number of NeoPixels, thus:

**DT = T / 10**

The idea now is to loop over each NeoPixel and wait this smaller amount of time **DT**. Once that time has elapsed, turn the NeoPixel off and move on to the next NeoPixel, etc.

Here's the previous code modified to do this:

Copy Code

    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Less Basic Timer
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Turn ON all the NeoPixels
      for (int p=0; p<10; p++) {
        CircuitPlayground.setPixelColor(p, 255, 255, 255);
      }
    
      // Compute DT
      unsigned long DT = 5000/10;
      
      // Turn OFF the NeoPixels one at a time, waiting DT each time
      for (int p=0; p<10; p++) {
        delay(DT);
        CircuitPlayground.setPixelColor(p, 0, 0, 0);
      }
      
      // Wait for button press to reset timer
      while (!CircuitPlayground.leftButton()   && 
             !CircuitPlayground.rightButton())  {
        // Do nothing, just waiting for a button press...
      }
    }
    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Less Basic Timer
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Turn ON all the NeoPixels
      for (int p=0; p<10; p++) {
        CircuitPlayground.setPixelColor(p, 255, 255, 255);
      }
    
      // Compute DT
      unsigned long DT = 5000/10;
      
      // Turn OFF the NeoPixels one at a time, waiting DT each time
      for (int p=0; p<10; p++) {
        delay(DT);
        CircuitPlayground.setPixelColor(p, 0, 0, 0);
      }
      
      // Wait for button press to reset timer
      while (!CircuitPlayground.leftButton()   && 
             !CircuitPlayground.rightButton())  {
        // Do nothing, just waiting for a button press...
      }
    }

As you can see, the `delay()` command has been moved inside a loop. The loop runs 10 times, so the `delay()` command gets called 10 times. However, the total amount of time counted remains the same 5 seconds as before.

#  Next Step

Hourglasses typically don't have buttons that are pressed to reset them like our Circuit Playground code is doing. An hourglass is reset by simply flipping it over and letting the sand run through in the other direction. How can we simulate this action with the Circuit Playground? Well, maybe we can use the accelerometer. Let's give that a try.

#  Flip Detect

by [ Carter Nelson ](/users/caternuson)

To make things easy, let's assume the hourglass timer will be used with the Circuit Playground facing up. The NeoPixels are on that side, so this makes sense. It also let's us use the Z axis of the accelerometer to detect when the Circuit Playground is flipped over. If you want more info on the accelerometer, see the [this guide](../../../../how-tall-is-it/hello-accelerometer).

The figure below shows a time history of the value returned from `CircuitPlayground.motionZ()` with the Circuit Playground facing up and down.

[ ![circuit_playground_accelo_time_hist.png](https://cdn-learn.adafruit.com/assets/assets/000/037/793/medium800/circuit_playground_accelo_time_hist.png?1480995359) __ ](/assets/37793)

The value of 9.8 m/s2 relates to earth gravity. With the Circuit Playground facing up, it is a positive value. With the Circuit Playground facing down, it is a negative value. So we can detect a flip by simply checking the sign of the value.

We start with the Circuit Playground face up and a positive value. The first step is to wait for the value to become negative. Then, once it is negative, we wait for it to become positive again. That's a flip!

Here's a simple sketch that demonstrates this logic being used to detect a flip and then play a tone.

Copy Code

    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Flip Detect
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Wait for Circuit Playground to be flipped over (face down)
      while (CircuitPlayground.motionZ() > 0) {};
    
      // A little debounce
      delay(500);
    
      // Wait for Circuit Playground to be flipped back over (face up)
      while (CircuitPlayground.motionZ() < 0) {};
    
      // Make a beep noise.
      CircuitPlayground.playTone(800,1000);
    }
    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Flip Detect
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Wait for Circuit Playground to be flipped over (face down)
      while (CircuitPlayground.motionZ() > 0) {};
    
      // A little debounce
      delay(500);
    
      // Wait for Circuit Playground to be flipped back over (face up)
      while (CircuitPlayground.motionZ() < 0) {};
    
      // Make a beep noise.
      CircuitPlayground.playTone(800,1000);
    }

The little lines of code that look like:

Copy Code

    
    
    while (CircuitPlayground.motionZ() > 0) {};
    
    
    while (CircuitPlayground.motionZ() > 0) {};

are called "parking loops". If we wanted them to actually do something, we would place that code in the `{}` brackets. In this case all we want to do is wait until the condition being tested becomes true. So the program execution just "parks" here until that happens.

The line of code with the small delay:

Copy Code

    
    
    delay(500);
    
    
    delay(500);

is needed to prevent false flip detection. This can occur as the processor runs fast enough that it might see a brief positive value immediately after the first negative value, due to noise or small amounts of real motion. By waiting a small amount of time before checking the accelerometer value again, we prevent this.

#  Next Step

OK, let's use this flip logic to alter our previous code so it behaves more like an hourglass. Instead of resetting the hourglass with the push buttons, we'll use this flip detect.

#  Basic Hourglass

by [ Carter Nelson ](/users/caternuson)

Let's add the flip detect logic from the previous section to the less basic timer code to make a basic hourglass.

Here's the code:

Copy Code

    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Basic Hourglass
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Turn ON all the NeoPixels
      for (int p=0; p<10; p++) {
        CircuitPlayground.setPixelColor(p, 255, 255, 255);
      }
    
      // Compute DT
      unsigned long DT = 5000/10;
      
      // Turn OFF the NeoPixels one at a time, waiting DT each time
      for (int p=0; p<10; p++) {
        delay(DT);
        CircuitPlayground.setPixelColor(p, 0, 0, 0);
      }
      
      // Wait for Circuit Playground to be flipped over (face down)
      while (CircuitPlayground.motionZ() > 0) {};
    
      // A little debounce
      delay(500);
    
      // Wait for Circuit Playground to be flipped back over (face up)
      while (CircuitPlayground.motionZ() < 0) {};
    }
    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Basic Hourglass
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Turn ON all the NeoPixels
      for (int p=0; p<10; p++) {
        CircuitPlayground.setPixelColor(p, 255, 255, 255);
      }
    
      // Compute DT
      unsigned long DT = 5000/10;
      
      // Turn OFF the NeoPixels one at a time, waiting DT each time
      for (int p=0; p<10; p++) {
        delay(DT);
        CircuitPlayground.setPixelColor(p, 0, 0, 0);
      }
      
      // Wait for Circuit Playground to be flipped over (face down)
      while (CircuitPlayground.motionZ() > 0) {};
    
      // A little debounce
      delay(500);
    
      // Wait for Circuit Playground to be flipped back over (face up)
      while (CircuitPlayground.motionZ() < 0) {};
    }

So at this point we have a basic working hourglass. It counts for a period of 5 seconds, turning off the NeoPixels one at a time, and can be reset by flipping the Circuit Playground over.

#  Changing Count Time

If you want to set the timer to a different amount of time, simply change this line of code:

Copy Code

    
    
    unsigned long DT = 5000/10;
    
    
    unsigned long DT = 5000/10;

and replace 5000 with whatever value you want. However, a better way to do this is to define this value globally at the top of the code. Try this - first, modify the code by adding a **#define** statement near the top as shown below.

Copy Code

    
    
    #include <Adafruit_CircuitPlayground.h>
    
    #define COUNT_TIME	5000	// milliseconds
    
    
    #include <Adafruit_CircuitPlayground.h>
    
    #define COUNT_TIME	5000	// milliseconds

Now change the line that computes **DT** as follows:

Copy Code

    
    
    unsigned long DT = COUNT_TIME / 10;
    
    
    unsigned long DT = COUNT_TIME / 10;

This makes it easier to find and change the value in the future.

#  Next Step

Try setting **COUNT_TIME** to something longer than 5 seconds, like 30 seconds:

Copy Code

    
    
    #define COUNT_TIME	30000	// milliseconds
    
    
    #define COUNT_TIME	30000	// milliseconds

Run this and watch what happens when the count gets to the end. It works fine, but since the total time (**COUNT_TIME**) is now longer, so is the delay (**DT**) at each NeoPixel. This makes it difficult to see the last bit of time elapsing. The last NeoPixel is on, then suddenly off.

So how can we indicate the time progress for each NeoPixel? How about fading them? That might work, let's give it a try.

#  Fading Hourglass

by [ Carter Nelson ](/users/caternuson)

Our previous code simply waited at each NeoPixel the computed amount of time** DT**, and then turned the NeoPixel off. Now let's change things so that the NeoPixel fades out over this period of time.

Basically, we need to go one level deeper on our time line. Now, within each time slice **DT**, instead of doing nothing, we'll be fading the NeoPixel. See the figure below.

[ ![circuit_playground_fading_time_line.png](https://cdn-learn.adafruit.com/assets/assets/000/037/829/medium800/circuit_playground_fading_time_line.png?1481053563) __ ](/assets/37829)

The value **N** is just an arbitrary number of steps over which the fading will occur. This further divides the time slice **DT** into smaller slices, called **FADE_DT** in the figure above.

The simplest way to fade a NeoPixel is to linearly change the setting from its starting value down to zero. The NeoPixels on the Circuit Playground have red, green, and blue LEDs in them, so we do the same thing for each of the color components individually. This idea is shown in the figure below.

[ ![circuit_playground_fading_time_line2.png](https://cdn-learn.adafruit.com/assets/assets/000/037/830/medium800/circuit_playground_fading_time_line2.png?1481053581) __ ](/assets/37830)

So at each of the fading time steps, we decrease the red, green, and blue values by a small amount. After doing this **N** times, the values will reach 0.

OK, here's our final code, with flip-to-reset and fading NeoPixel grains of sand.

Copy Code

    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Fading Hourglass
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    #define COUNT_TIME    30000 // milliseconds
    #define FADE_STEPS    100   // NeoPixel fade steps
    #define R_SAND        255   // Sand color RED value
    #define G_SAND        255   // Sand color GREEN value
    #define B_SAND        255   // Sand color BLUE value
    
    unsigned long DT;
    float r, g, b;
    float dr, dg, db;
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      Serial.begin(9600);
      
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    
      // Compute per NeoPixel wait time
      DT = COUNT_TIME / 10;
      
      // Compute the color value change per fade step
      dr = float(R_SAND) / float(FADE_STEPS);
      dg = float(G_SAND) / float(FADE_STEPS);
      db = float(B_SAND) / float(FADE_STEPS);
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Turn ON all the NeoPixels
      for (int p=0; p<10; p++) {
        CircuitPlayground.setPixelColor(p, uint8_t(R_SAND), 
                                           uint8_t(G_SAND), 
                                           uint8_t(B_SAND));
      }
      
      // Loop over each NeoPixel
      for (int p=0; p<10; p++) {
        // Set the start RGB values
        r = float(R_SAND);
        g = float(G_SAND);
        b = float(B_SAND);
        // Loop over each fading step
        for (int n=0; n<FADE_STEPS; n++) {
          delay(DT/FADE_STEPS); // Per fade step delay
          r = r - dr;           // Decrease the red value
          g = g - dg;           //    "      "  green "
          b = b - db;           //    "      "  blue  "
          CircuitPlayground.setPixelColor(p, uint8_t(r),
                                             uint8_t(g),
                                             uint8_t(b));      
        }
      }
      
      // Wait for Circuit Playground to be flipped over (face down)
      while (CircuitPlayground.motionZ() > 0) {};
    
      // A little debounce
      delay(500);
    
      // Wait for Circuit Playground to be flipped back over (face up)
      while (CircuitPlayground.motionZ() < 0) {};
    }
    
    
    ///////////////////////////////////////////////////////////////////////////////
    // Circuit Playground Fading Hourglass
    //
    // Author: Carter Nelson
    // MIT License (https://opensource.org/licenses/MIT)
    
    #include <Adafruit_CircuitPlayground.h>
    
    #define COUNT_TIME    30000 // milliseconds
    #define FADE_STEPS    100   // NeoPixel fade steps
    #define R_SAND        255   // Sand color RED value
    #define G_SAND        255   // Sand color GREEN value
    #define B_SAND        255   // Sand color BLUE value
    
    unsigned long DT;
    float r, g, b;
    float dr, dg, db;
    
    ///////////////////////////////////////////////////////////////////////////////
    void setup() {
      Serial.begin(9600);
      
      // Initialize the Circuit Playground
      CircuitPlayground.begin();
    
      // Compute per NeoPixel wait time
      DT = COUNT_TIME / 10;
      
      // Compute the color value change per fade step
      dr = float(R_SAND) / float(FADE_STEPS);
      dg = float(G_SAND) / float(FADE_STEPS);
      db = float(B_SAND) / float(FADE_STEPS);
    }
    
    ///////////////////////////////////////////////////////////////////////////////
    void loop() {
      // Turn ON all the NeoPixels
      for (int p=0; p<10; p++) {
        CircuitPlayground.setPixelColor(p, uint8_t(R_SAND), 
                                           uint8_t(G_SAND), 
                                           uint8_t(B_SAND));
      }
      
      // Loop over each NeoPixel
      for (int p=0; p<10; p++) {
        // Set the start RGB values
        r = float(R_SAND);
        g = float(G_SAND);
        b = float(B_SAND);
        // Loop over each fading step
        for (int n=0; n<FADE_STEPS; n++) {
          delay(DT/FADE_STEPS); // Per fade step delay
          r = r - dr;           // Decrease the red value
          g = g - dg;           //    "      "  green "
          b = b - db;           //    "      "  blue  "
          CircuitPlayground.setPixelColor(p, uint8_t(r),
                                             uint8_t(g),
                                             uint8_t(b));      
        }
      }
      
      // Wait for Circuit Playground to be flipped over (face down)
      while (CircuitPlayground.motionZ() > 0) {};
    
      // A little debounce
      delay(500);
    
      // Wait for Circuit Playground to be flipped back over (face up)
      while (CircuitPlayground.motionZ() < 0) {};
    }

#  Questions and Code Challenges

by [ Carter Nelson ](/users/caternuson)

The following are some questions related to this project along with some suggested code challenges. The idea is to provoke thought, test your understanding, and get you coding!

While the sketches provided in this guide work, there is room for improvement and additional features. Have fun playing with the provided code to see what you can do with it.

#  Questions

  * How would this code behave if the Circuit Playground had more than 10 NeoPixels? How about less?
  * What is the maximum amount of time that the timer can be set for?
  * Why is `delay()` called before setting the NeoPixel colors in the loop?
  * Why were floats used in the Fading Hourglass sketch for the RGB values? (hint: what does `int value = 5/3;` give?)

#  Code Challenges

  * Use `playTone()` to add an audio alarm when the countdown ends.
  * Change the fade effect to be non-linear.
  * Allow for a flip reset during the count period.
