# Circuit Playground Bike Light

_Captured: 2017-08-08 at 18:48 from [www.digikey.com](https://www.digikey.com/en/maker/projects/circuit-playground-bike-light/b29b1e1076d44f95a34d06473d230274)_

### ![](https://www.digikey.com/-/media/MakerIO/Images/projects/33153e367d47440583fc5fda44100e20.jpg?ts=f5d2f67d-a181-4258-b4bc-f40870da7db8)

**Overview**

In this guide we will use our Circuit Playground to create a customizable bike light. We'll look at how we define colors in code and use that to make some fun animations with the NeoPixels. We'll provide some example animations you can customize. Or you can modify and adapt the examples to try and create your own.

![Blinky bikey fun!](https://www.digikey.com/maker-media/6ddfa082-88d8-45e4-be05-43bd21cbbe40)

> _Blinky bikey fun!_

In a world of blinking red bike lights, add some color and pizazz to stand out!

**Required Parts**

In addition to a Circuit Playground, you will need some form of battery power so you can ride around outside with your bike light. Choose an option that works for how you plan to mount things to your bike.

![Circuit Playground](https://www.digikey.com/maker-media/bca85de1-b954-45bb-a760-a98156c2ed36)

> _Circuit Playground_

![3 x AAA Battery Holder](https://www.digikey.com/maker-media/d60d93bd-a5a4-4c2f-bc6c-36fdb59010a5)

> _3 x AAA Battery Holder_

[3 x AAA Battery Holder with On/Off Switch and 2-Pin JST](https://www.digikey.com/product-detail/en/adafruit-industries-llc/727/1528-1151-ND/5353611) (also need [AAA batteries](http://www.digikey.com/products/en/battery-products/batteries-non-rechargeable-primary/90?k=&pkeyword=&pv32=3&FV=ffe0005a&mnonly=0&newproducts=0&ColumnSort=0&page=1&quantity=0&ptm=0&fid=0&pageSize=500))

![Lithium Ion Polymer Battery - 3.7v 500mAh](https://www.digikey.com/maker-media/2f037915-bd3a-4935-ad35-7e2888091483)

> _[Lithium Ion Polymer Battery - 3.7v 500mAh](https://www.digikey.com/product-detail/en/adafruit-industries-llc/1578/1528-1841-ND/5054539)_

(or similar)

![JST 2-pin Extension Cable with On/Off Switch](https://www.digikey.com/maker-media/f4541fdb-f859-4db9-b01d-af879db76da2)

> _[JST 2-pin Extension Cable with On/Off Switch](https://www.digikey.com/product-detail/en/adafruit-industries-llc/3064/1528-1679-ND/6022074)_

(useful if using LiPo)

If you go with the LiPo battery, be sure you have a way to [charge it](https://www.adafruit.com/category/575).

**Before Starting**

If you are new to the Circuit Playground, you may want to first read these overview guides.

This project will use the Arduino IDE. Make sure you have added the board support for the Circuit Playground as well as installed the Circuit Playground library. **MUST DO BOTH**. This is covered in the guides linked above.

**Hello Color**

![Hello Color](https://www.digikey.com/maker-media/4ac9e0be-8e91-45e0-a4b1-eed01f2784b0)

> _Hello Color_

There's a rainbow of colors out there in the world. Purple. Lime green. Bright blues. Mellow yellows. etc. In order to be able to use them in our projects, we need some way to describe them. It turns out that all the colors of the rainbow can be described in terms of a combination of only three colors: Red, Green, and Blue. This is referred to as [additive color](https://en.wikipedia.org/wiki/Additive_color).

![Additive color mixing](https://www.digikey.com/maker-media/991ba854-f2d4-4fcc-9218-31a8d3493f22)

> _Additive color mixing_

In the image above you can see the basic idea for how this works. Red is just red. Green is just green. Blue is just blue. But if you want yellow then you combine red and green. The purple color is called magenta and is a combination of red and blue. The light blue color is called cyan and is a combination of green and blue. What happens if you combine all three? Well, you get white, as shown in the middle of the diagram.

But we can also create many more colors by picking how much we mix each of the red, blue, and green together. Here is a much more colorful wheel of color.

![Colorful wheel of color](https://www.digikey.com/maker-media/91ebca89-2118-4037-bbf8-09993e72fda4)

> _Colorful wheel of color_

For example, orange is mostly red with a little bit of green. Pink is mostly red with a little bit of blue. How do we come up with the right mixture of red, green, and blue for all of these pretty colors? Luckily there are lots of handy tools to help us out. In fact, you can get a very easy to use one by simply going to [Google](https://www.google.com/) and doing a search for 'rgb color picker'.

![RGB Color Picker](https://www.digikey.com/maker-media/9fbd3430-71a6-4f14-b4b0-b044d7d5548d)

> _RGB Color Picker_

Of course you'll get a lot of search results as well. But this is such a commonly used tool, that Google just throws one up for you to use right away. Here's a breakdown of how to use it.

![Breakdown of how to use the RGB Color Picker](https://www.digikey.com/maker-media/a889bdd7-f805-40f5-9f4c-a0a831ae9938)

> _Breakdown of how to use the RGB Color Picker_

Use slider (1) to pick a color. Then move slider (2) around to change how light or dark the color is. The resulting color is shown in (3) along with some cryptic numbers.

Let's look at what those numbers mean.

**Colors in Code**

The color picker above provides information on the current color in two formats. The one that looks like #4286f4 is referred to as 'hex', which is short for hexadecimal. The one that looks like rgb(66, 134, 244) is referred to as 'rgb' (are-gee-bee), r for red, g for green, b for blue. They are both describing the same color but in different ways. In code, you'll typically use one form or the other, or sometimes swap between them. Basically:

    * Use hex to describe the color with a single value
    * Use rgb to more intuitively describe a color or for easy access to a specific color channel

**RGB Color Codes**

This one is pretty easy to understand. You just specify the three separate values for red, green, and blue. For example:

**rgb(66, 134, 244)**

is setting red to 66, green to 134, and blue to 244. The values can range from 0 to 255. What's so magic about 255? Why not 100 or 1000? It has to do with these being 8-bit values. In this coloring scheme, each color is specified by 8-bits. And the range of values that can be specified by 8-bits is 0 to 255 (2^8-1). Here is how you would specify the three primary colors:

Copy Code
    
    
    CircuitPlayground.setPixelColor(0, 255,   0,   0);  // red  
    CircuitPlayground.setPixelColor(0,   0, 255,   0);  // green  
    CircuitPlayground.setPixelColor(0,   0,   0, 255);  // blue

But of course you can specify any random combination of values, with each ranging from 0 to 255.

Copy Code
    
    
    CircuitPlayground.setPixelColor(0,  98,  12, 143);  // ??  
    CircuitPlayground.setPixelColor(0,   0, 251,   1);  // ??  
    CircuitPlayground.setPixelColor(0,  176, 42,  23);  // ??

And just if you're curious, there are 2^24 = 16,777,216 possible color combinations. Thats a lot of colors, yo!

**HEX Color Codes Part 1**

This one is a little more difficult to understand. First, you need to understand hexadecimal. We all grow up using a decimal numbering system. This means the numbering system is based on ten unique values, which (in English) we give the symbols: 0,1,2,3,4,5,6,7,8,9. With hexadecimal, the numbering system has sixteen unique values instead of ten. To represent them, the first ten are the same as before and the remaining six use the first six letters of the alphabet. So we have 0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F.

Let's count to 20 using both decimal (DEC) and hexadecimal (HEX).

![DEC and HEX count](https://www.digikey.com/maker-media/0c491f6b-684a-44da-89bc-7f4e3222c17e)

> _DEC and HEX count_

Note how everything is the same up to 9 (i.e. the first ten values). Once we reach 10, we've run out of decimal digits, so we need to increment. However, we haven't run out of hexadecimal digits, so we just keep counting. We run out of hexadecimal digits when we reach 16, at which point we increment like we did when we reached 10 in decimal.

One key thing to note is what the maximum 8-bit value looks like in hex. Remember this was 255 in decimal. That becomes FF in hex. To go one higher, say to 256, first we'd need an extra bit, and then the hex would become 100.

Confusing? Yeah it can be. It can take some time, but eventually you'll get the idea. There are special calculators called **programmers calculators** that help out with these conversions.

You can also get away with just typing the conversion in to Google. For example, try Googling the phrase "256 in hex".

**Is it DEC or HEX?**

We also need some way of specifying to our program if we are using decimal or hexadecimal. For example, consider the following assignment:

Copy Code
    
    
    someValue = 10;

Is that the decimal 10 we all know and love, or is it that weird 10 in hexadecimal which is actually 16 in decimal? To sort this out, special character sequences are used in front of the number to let the program know which one it is. The default is decimal, so we just need something for hexadecimal. In Arduino programs, we prefix hexadecimal numbers with **0x**. Then we can do things like this:

Copy Code
    
    
    someValue1 = 10;    // this is decimal 10  
    someValue2 = 0x10;  // this is hexadecimal 10 (decimal 16)

**HEX Color Codes Part 2**

The idea with the HEX color code is to combine the red, green, and blue values into one value. This way we can specify a color with a single value, instead of three separate values.

Since each color uses 8-bits, we end up needing 24-bits to store the information. You can think of it as just chaining the three separate 8-bits of color info into one 24-bit sequence. Red is 'first', then green, and finally blue. Something like this:

**0xRRGGBB**

Since we are using hexadecimal to specify each 8-bit value, the range for each is from 0x00 to 0xFF. For example, here is how you would specify the three primary colors:

And others colors will be a mixture of values. Here's the one from the color picker:

![HEX Color Codes Part 2](https://www.digikey.com/maker-media/0f33a26f-99bb-4e81-9c6a-557d84f87daa)

> _Which would look like this in code:_

Note that case typically doesn't matter when specifying hex numbers. That is:

**0xff = 0xFF**

Picking one or the other is just a matter of style.

**Nerdy Nerd Joke**

Decimal is base ten. Hexadecimal is base sixteen. But you can actually have a numbering system with any base you want. Humans tend to like base ten because we have ten fingers. Computers really like base two, otherwise known as binary, because in their world things are either on or off. And in a base two universe, you can tell jokes like this:

    * _**There are 10 kinds of people in this world. Those that know binary and those that don't.**_
![Nerdy Nerd Joke](https://www.digikey.com/maker-media/1c6265ee-f8b8-4636-997c-4ad6c09d8409)

> _Nerdy Nerd Joke_

**Hello NeoPixel**

Don't do this with your eyes, but let's look inside a NeoPixel to see what's going on. Here's a nice macro photo of a single NeoPixel.

![A look inside a NeoPixel](https://www.digikey.com/maker-media/ba867ab1-0107-496e-89ae-0ecdc30bf2b4)

> _A look inside a NeoPixel_

There are three tiny little LEDs in there. A blue one, a red one, and a green one. Each one is controlled by the circuit next to them which acts like a brain. This is what receives the NeoPixel commands and does the actual turning on of the LEDs.

The Circuit Playground has 10 of these NeoPixels arranged in a circular pattern as shown below. All we need to do is write programs to tell them what colors we want.

![Write programs for arranged NeoPixel colors](https://www.digikey.com/maker-media/369d8782-88ee-419c-923b-ce958bd1a7ec)

> _Write programs for arranged NeoPixel colors_

So we can use the red, green, and blue LEDs in each NeoPixel to generate various colors. We just specify a color and the NeoPixel will take care of turning on the three LEDs in the right amount to generate that color.

**Library Reference**

There are two main functions in the Circuit Playground library for use with NeoPixels, clearPixels() and setPixelColor() . The first one simply turns off all of the NeoPixels. The second one is more fun, as it is how we turn on NeoPixels and specify a color. You can use it with either the rgb color values or the hex value to specify a color. Check out the library reference [here](https://learn.adafruit.com/circuit-playground-lesson-number-0/neopixels#library-reference) and [here](https://caternuson.github.io/Adafruit_CircuitPlayground/setPixelColor.html) and the example sketch that comes with the library:

**File -> Examples -> Adafruit Circuit Playground -> Hello_CircuitPlayground -> Hello_NeoPixels**

Here's a simple program that turns on all the NeoPixels to the specified COLOR . You can use to play around with various color values.

Use the color picker from the previous selection and find a color you like. Then take the hex value shown and modify the following line of code. Note that the Google color picker has a **#** in front of the value. Be sure to change that to **0x** in the code as shown:

Here's what I got when I tried out that value.

![Library Reference](https://www.digikey.com/maker-media/b099445c-9930-42b6-af0b-3b5e1b3734ea)

> _Library Reference_

They kind of look the same. A computer monitor and a NeoPixel are pretty different, so it's not going to be an exact match. But at least it's not red or orange or something.

**Turning Off a Single NeoPixel**

There's only one command for turning off the NeoPixels, clearPixels() , and it turns them all off. But what if you wanted to turn just one NeoPixel off. The answer is pretty simple. 'Off' is just no color, or the equivalent for 'black'. So we use the setPixelColor() command on the pixel we want and specify the values of 0x000000 or (0, 0, 0). For example, here's how to turn off NeoPixel 6:

**Setting Brightness**

The one other useful NeoPixel function is setBrightness() . It can take a value from 0 to 255, with higher numbers being brighter. You typically call this just once at the beginning of your code, in the setup() function, to set the overall brightness for all NeoPixels. It can not be used to change the brightness of a single NeoPixel.

**Basic NeoPixel Animation**

All NeoPixel animation comes down to simply turning on and off the pixels and/or changing their color. That's it. Everything is done by playing with three basic things:

      * Location - What pixel(s) to turn on/off?
      * Color - What color to use?
      * Time - How long to stay on/off?

Figuring out the code for complex animations can be tricky. In that case, taking an approach as described in the NeoAnim guide can help.

However, for our bike light, we will keep things simple and just use a basic loop. By changing various parameters within the loop, we can create some fun animations that will make for a cool bike light.

For example, here's a basic spinner animation.

Our location parameter of the animation is controlled by the pixel value in the loop.

Both the color parameter ( COLOR ) and time parameter ( RATE ) of the animation are set by global values at the top of the sketch.

Play around with changing the values for COLOR and RATE and see what happens. You can use the color picker to come up with the color values.

More 'complex' animations can be created by doing things like having more than one loop, changing more than one pixel at a time, using more than one color, etc. What follows are several examples to illustrate this. After playing with them and looking through them, try and come up with your own animation.

**The Flasher**

This first one is your basic classic blinking flasher. Just like pretty much every bike light out there. Basically just turn all the NeoPixels on, then turn them off, then back on again, etc.

Pretty simple, but it does get people's attention. Play around with these two lines of code:

Try changing the COLOR to **0xff07ee**. What color is that? Want to make it blink faster? Try lowering FLASH_RATE down to say something like **100** or **50**.

Congratulations. You now have a bike light you can customize to your favorite color!

But why just have a boring old blink blink blink? We can do so much more...

**The Spinner**

This one has kind of a cool UFO look to it. Set any two pixels (0 to 9) and they will go round and round. Change the color to whatever you want and speed it up or slow it down to your liking.

**The Cylon**

Want to look like an [evil robot](https://en.wikipedia.org/wiki/Cylon_\(Battlestar_Galactica\)) and/or a [cool car from the 80's](https://en.wikipedia.org/wiki/KITT)? By your command. I mean, OK Michael. I mean...oh never mind. Here's the code. It scans the pixels back and forth. This one looks best with the scans moving horizontally.

**The Bedazzler**

The idea with this one is to just randomly flash random colors on random pixels. This is a good example of where using the (r,g,b) version of setPixelColor() is useful. We'll generate a random red value, a random green value, and a random blue value. Then we just call setPixelColor(pixel, r, g, b) for a random pixel.

This could have been done using the hex value, but coding this way is more readable and intuitive.

**The Rainbow Chaser**

OK, now we're getting a little more colorful. Specify 10 colors using hex values in the colors[] array. These colors will be displayed on the 10 NeoPixels and the pattern will be rotated round and round.

**The All Of Them**

Now what if you're out riding around and get tired of the current animation and want to change it. Ride all the way home and reload a different animation? Nah. Let's see how we can have them all loaded and then choose the one we want using the buttons on the Circuit Playground.

**Doing Two (or more) Things At Once**

As simple as the idea of changing animations with a button press is, it has some surprising complexities. At it's lowest level, the brain on the Circuit Playground can only do one thing at a time. So if it's busy turning NeoPixels on and off, how can it check on button presses?

There are various approaches. For our bike light, we will use the simplest of them. However, for an excellent overview of more complex approaches (including using interrupts), check out this three part series. The ideas discussed in these guides could be used on the Circuit Playground.

What we will do is take advantage of the fact that all of our animation loops run fairly fast. This makes it possible to simply check for any button presses at the beginning (or end) of the animation loop. Then, if a button is pressed, take some action - like move to the next animation. This isn't perfect and has some issues, as you'll see.

To do this, we first take all of the animation code from our previous sketches and move them into functions that have the form:

We'll create a function for each animation. The while() loop will drive the animation and will continue as long as no buttons are pressed.

Then, our main Arduino loop() will look something like this:

So the first animation is launched with a call to animation1() . That will run until a button is pressed. When a button is pressed, the animation function exits and the next animation function animation2() is called. Which runs until a button is pressed, etc.

The delay() is needed so that you don't cycle through the animations super fast when you press a button. This is a simple form of debounce.

Here's the final code:

**Issues**

With the above code loaded and running on the Circuit Playground, try changing the animations by pressing either of the two buttons. Did it work? If not try pressing it again. Work that time?

So you might notice that the button response is a little sluggish. Sometimes it will change, sometimes it won't. This is the main issue with the simple approach we've taken for checking button presses. The responsiveness is coupled to the speed of the animation. You could make the problem even worse by slowing down an animation. Then the button is checked even less frequently and becomes even more sluggish.

Kind of annoying, isn't it? If you're motivated to try and make it better, read the guides linked above.

**Making the Bike Light**

The Circuit Playground bike light is meant to be rear facing. It doesn't generate enough light to illuminate the path in front of you.

You can mount it any old way depending on what your bike seat looks like and what other items you might have. The seat and/or seat post are good ideas. But could be a rear fender, storage rack, pannier, etc. Just be careful not get any loose wires caught up in the tire spokes.

Here's what I came up with using one of those small little under the seat packs.

![The battery can go in the seat pack](https://www.digikey.com/maker-media/d48ab828-9145-492f-bdc2-7f37dd4d6b64)

> _The battery can go in the seat pack._

![Zip it close and let the on/off switch hang below.](https://www.digikey.com/maker-media/7c570c1f-f436-4452-9616-d3160a7dfc45)

> _Then zip it close and let the on/off switch hang below._

![Use zip ties to attach Circuit Playground to seat pack](https://www.digikey.com/maker-media/5d34c60c-237c-4479-9c33-29517a645866)

> _Use zip ties to attach the Circuit Playground to the seat pack._

![Cut zip ties flush](https://www.digikey.com/maker-media/868bc76b-c166-4977-a21a-f5466943fb67)

> _Cut zip ties flush_

Cut zip ties flush.

![Good to go](https://www.digikey.com/maker-media/9646108c-2846-4882-99ed-6b782315bf8f)

> _Good to go_

Good to go.

**Questions and Code Challenges**

The following are some questions related to this project along with some suggested code challenges. The idea is to provoke thought, test your understanding, and get you coding!

While the sketches provided in this guide work, there is room for improvement and additional features. Have fun playing with the provided code to see what you can do with it. Or do something new and exciting!

**Questions**

      * Is there any green in the color defined by 0xF0000D?
      * What color is defined by 0xFFBAD2?
      * How do you turn on more than one NeoPixel?
      * What is the hexadecimal value 0x04 in decimal?

**Code Challenges**

      * Use the slide switch to create a way to turn off/on all animations (power saver).
      * Use the light meter to automatically turn on animations when it gets dark.
      * Use the accelerometer as an input to an animation. (ex: spin/blink faster with acceleration).
      * Make your own animation!
