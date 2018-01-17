/*
 * test.cpp
 *
 * Created: 26.05.2014 20:22:11
 *  Author: MrLeeh
 */ 


#include <avr/io.h>
#include <util/delay.h>

int button_pressed_counter = 0;
bool button_pressed()
{
	bool b = !(PINB & (1 << PB3));
	if (b)
		button_pressed_counter++;
	else
		button_pressed_counter = 0;
	
	if (button_pressed_counter >= 10)
		{
			button_pressed_counter = 0;
			return true;	
		}
	return false;
}

int main(void)
{
	//Pin 0: Ausgang, Pin 1: Eingang
	DDRB |= (1 << DDB1);	//relay switch
	DDRB |= (1 << DDB0);	//led
	DDRB &= ~(1 << DDB3);	//button
	PORTB |= (1 << PINB3);	//pullup for button
	DDRB |= (1 << DDB4);	//shutdown switch for raspberry
	
	bool led_on = false;
	bool power_on = false;
	bool shutdown_signal = false;
	int state = 0;
	
	int second_counter = 0;
	bool second_trigger = false;
	int shutdown_counter = 0;
	
    while(true)
    {
		switch (state)
		{
			case 0:	//Power on
				led_on = true;
				power_on = true;
				if (button_pressed())
				{
					second_counter = 0;
					shutdown_counter = 0;
					state = 1;	
				}					
				break;
				
			case 1:	//Shutdown
				second_counter++;
				led_on = second_trigger;
				if (shutdown_counter == 30)
					state = 2;
				if (button_pressed())
				{
					shutdown_counter = 0;
					state = 0;
				}				
				break;
				
			case 2:	//Power off
				power_on = false;
				led_on = false;
				if (button_pressed())
					state = 0;
				break;
		}
				
		//led switched on
		if (led_on)
			PORTB |= (1<<PB0);
		else
			PORTB &= ~(1<<PB0);			
			
		//relay switched_on
		if (power_on)
			PORTB |= (1<<PB1);
		else
			PORTB &= ~(1<<PB1);
			
		//Shutdown signal for Raspberry Pi
		shutdown_signal = state == 1;		
		if (shutdown_signal)
			PORTB |= (1<<PB4);
		else
			PORTB &= ~(1<<PB4);
			
		if (second_counter >= 11)
		{
			second_counter = 0;
			second_trigger=!second_trigger;
			shutdown_counter++;
		}
		
		_delay_ms(100);
	}		
}