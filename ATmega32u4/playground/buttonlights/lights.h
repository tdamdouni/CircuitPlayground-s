#ifndef PLAYGROUND_LIGHTS_H
#define PLAYGROUND_LIGHTS_H

#define CIRCUIT_PLAYGROUND_NUMBER_OF_PIXELS 10

enum Direction { clockwise, counter_clockwise };

void light_loop(int delay_millis, int step, Direction direction=clockwise);
void pulse(int number_of_pulses, int delay_millis);

#endif
