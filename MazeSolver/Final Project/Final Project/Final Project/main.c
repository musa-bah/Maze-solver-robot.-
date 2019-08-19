#define F_CPU (16000000)
#define BAUDRATE (9600)
#define BAUD_PRESCALE (F_CPU/BAUDRATE/16 - 1)

#include <avr/io.h>
#include <util/delay.h>
#include "bluetooth.h"
#include "Ultrasonic.h"
#include "motor_control.h"

int main(void)
{
	int autoControl = 0;
	
	// Initiations
	InitBluetooth();
	InitMotorControl();
	
	DDRB = (1 << PORTB5); // set the pin connected to the on board led as output
	
	while(1)
	{	
		
		while(autoControl == 1)
		{
			double distLeft;
			double distRight;
			double distFront;
			
			if(distLeft < 10 && distFront < 10 && distRight < 10)
			{
				back(180);
				_delay_ms(200);
				stop();
			}
			
			
			if (distFront > 10)
			{
				forward(180);
				_delay_ms(200);
				stop();
			}
			
			else if (distRight > 10)
			{
				right(120);
				_delay_ms(100);
				stop();
			}
			
			else if (distLeft > 10)
			{
				left(120);
				_delay_ms(100);
				stop();
			}
			
			else
			{
				left(180);
				_delay_ms(200);
				stop();
			}
		}
		
		while(autoControl == 0)
		{
			char keystroke = receiveByte();
			int delayTime = 50;
			int moveSpeed = 255;
			int turnSpeed = 200;
			
			/* How this works:-
			  - Receives a keystroke.
				W moves forward
				A turns left
				D turns right
				S moves backward 
				
		     The on-board led blinks when it receives a command. */
			
			// turn left
			if(keystroke == 'a')
			{
				left(turnSpeed); // motor control
				PORTB |= (1 << PORTB5); // turn the led on
				_delay_ms(delayTime);
				PORTB &= ~(1 << PORTB5);
				stop();
			}
			
			// move forward
			else if(keystroke == 'w')
			{
				forward(moveSpeed);
				PORTB |= (1 << PORTB5);
				_delay_ms(delayTime);
				PORTB &= ~(1 << PORTB5);
				stop();		
			}
			
			// turn right
			else if(keystroke == 'd')
			{
				right(turnSpeed);
				PORTB |= (1 << PORTB5);
				_delay_ms(delayTime);
				PORTB &= ~(1 << PORTB5);
				stop();
			}
			
			// move backwards
			else if(keystroke == 's')
			{
				back(moveSpeed);
				PORTB |= (1 << PORTB5);
				_delay_ms(delayTime);
				PORTB &= ~(1 << PORTB5);
				stop();
			}
			
			// return to auto mode
			else if(keystroke == 'y')
				autoControl = 1;
			
			// output invalid key
			else
				sendString("Inv key.\n\0");
			
		}
	}
}

