# moonfairies-CircuitPlayground

Drawing in midair with light

This sketch runs on a Circuit Playground and lets you turn LEDs on and off
with a simple capacitive contact, and change colors with another one.

Additionally, it can use the built-in accelerometer to figure out which
direction is currently down, and use that to choose a diagonal pair of LEDs
to light, which maintains its orientation as the Circuit Playground moves
around.

To build this, attach the Circuit Playground to the end of a stick, with
the LEDs facing away.  Attach a small lithium ion cell to power it, and
connect wires to the GND, 6, and 9 pads.  Run those to a set of copper
tape or similar contacts near the other end of the stick, with the GND
one in the middle.  By wrapping your hand around the ground contact, you
can turn the LEDs on by touching the pad for the 6 contact (I put this
in front of the ground contact, for easy operation with a finger while
drawing) and you can advance the color by touching the pad for the 9
contact (I put this one in back of the ground contact, so I don't hit
it accidentally).  The color change operation gives a beep as feedback.

You can reset the color sequence by moving the slide switch left and
right (you get a low beep and the pin 13 LED flashes to acknowledge the
reset).
