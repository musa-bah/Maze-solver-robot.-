#ifndef _ultrasonic_h
#define _ultrasonic_h

#include "pin_map.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int timer, count, duty;
void InterruptInit()
{
	sei();
	/*** Using 8 pre scaler. ***/
	TCCR1B |= (1<<CS11);

	/*** Set trig as output. ***/
	DDRC |= (1<<US_TRIG);

	/*** Interrupt triggered by PCINT12 ***/
	PCICR  |= (1<<PCIE1);
	PCMSK1 |= (1<<PCINT12);
	PCIFR &= ~(1<<PCIF1);
}

ISR(PCINT1_vect)
{
	/*** Checks if the ECHO is HIGH and starts the timer. ***/
	if (PINC & (1 << PINC4))
	{
		TCNT1 = 0;
	}
	
	else
	{
		timer = (TCNT1);
	}
}

void distance_cm(int timer)
{
	count = (timer*0.5)/58;
	duty = timer/13.8;
}

void trig()
{
	PORTC |= (1<<US_TRIG);
	_delay_us(10);
	PORTC &= ~(1<<US_TRIG);
}

#endif