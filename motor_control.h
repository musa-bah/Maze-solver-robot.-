#ifndef	_MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H 

#include <avr/io.h> 
#include <avr/interrupt.h>
#include "pin_map.h"

/****************** Timer needs to be set up before using this function *******************/

//    The direction of the car's movement
//  ENA   ENB   IN1   IN2   IN3   IN4   Description
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Move forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Move backwards
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Turn left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Turn right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Stopped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Stopped
//  LOW   LOW   N/A   N/A   N/A   N/A   Enables are off

void InitMotorControl()
{
	// enable the pins 5, 6, 7, 8, 9, 11 as outputs
	// ENA 5
	// ENB 6
	// IN1 7
	// IN2 8
	// IN3 9
	// IN4 11
	DDRD = DDRD | 0b11100000;
	DDRB = DDRB | 0b00001011;
	sei();
	TCCR0A = 0xA3;
	TCCR0B = 0x04;
	TCNT0 = 0x00;
	return;
}

void forward(int speed)
{
	PORTD = 0b11100000;
	PORTB = 0b00001000; 
	
	if(speed >=0 || speed <= 255) {
		OCR0A = speed;
		OCR0B = speed;		
	} 
	
	return;
}

void back(int speed)
{
	PORTD = 0b01100000;
	PORTB = 0b00000011;
	
	if(speed >=0 || speed <= 255) {
		OCR0A = speed;
		OCR0B = speed;
	}
	
	return;
}

void right(int speed)
{
	PORTD = 0b11100000;
	PORTB = 0b00000010;
	
	if(speed >=0 || speed <= 255) {
		OCR0A = speed;
		OCR0B = speed;
	}
	
	return;
}

void left(int speed)
{
	PORTD = 0b01100000;
	PORTB = 0b00001001;
	
	if(speed >=0 || speed <= 255) {
		OCR0A = speed;
		OCR0B = speed;
	}

	return;
}

void stop()
{
	PORTD = 0b01100000;
	PORTB = 0b00000000;
	
	return;	
}



#endif

