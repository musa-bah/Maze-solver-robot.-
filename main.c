#define F_CPU (16000000)
#define BAUDRATE (9600)
#define BAUD_PRESCALE (F_CPU/BAUDRATE/16 - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <avr/interrupt.h>
#include "pin_map.h"
#include "Ultrasonic.h"
#include "Servo.h"
#include "move_timer_setup.h"
#include "LineTracker.h"
#include "bluetooth.h"

//Function prototypes
void ServoPosition(int angle);
void Measure_Distance();
void InitiateSensor();
void Autonomous_Mode();
void bluetoothControl();
void Timer_Init();

//Global Variables
int angle;
int Middle_Distance;
int Left_Distance;
int Right_Disatance;
int Switch = 0;
int i;
char Move;
int stopwatch = 0;

int main(void)
{
	// Initiations
	sei();
	UltraSonicInit();
	ServoInit();
	InitiateSensor();
	MotorsInit();
	LineTrackerInit();
	Timer_Init();
	InitBluetooth();
	
	DDRB = (1 << PORTB5); // set the pin connected to the on-board led as output
		
	while(1)
	{	
		Autonomous_Mode();
			
		//Start manual mode.
 		// while (Switch == 1)
 		//{
		//	bluetoothControl();
		//}
			
	}
	return 1;
}

void bluetoothControl()
{
	char keystroke = receiveByte();
	int delayTime = 50;
	int moveSpeed = 255;
	int turnSpeed = 200;
	
	// turn left
	if(keystroke == 'a')
	{
		Left(turnSpeed); // motor control
		_delay_ms(delayTime);
		Stop();
	}
	
	// move forward
	else if(keystroke == 'w')
	{
		Forward(moveSpeed);
		PORTB |= (1 << PORTB5);
		_delay_ms(delayTime);
		PORTB &= ~(1 << PORTB5);
		Stop();
	}
	
	// turn right
	else if(keystroke == 'd')
	{
		Right(turnSpeed);
		PORTB |= (1 << PORTB5);
		_delay_ms(delayTime);
		PORTB &= ~(1 << PORTB5);
		Stop();
	}
	
	// move backwards
	else if(keystroke == 's')
	{
		Backward(moveSpeed);
		PORTB |= (1 << PORTB5);
		_delay_ms(delayTime);
		PORTB &= ~(1 << PORTB5);
		Stop();
	}
	
	// output invalid key
	else
	sendString("Inv key.\n\0");
	return;
}

void Autonomous_Mode()
{
	InitiateSensor();
		Forward(200);
		_delay_ms(700); //This was 1 seconds.
		Stop();
		Measure_Distance();
		
		if ((Right_Disatance < 30 ) && (Left_Distance < 30 ))
		{
			Forward(200);
		}
		
		else if(Left_Distance > Right_Disatance)
		{
			Left(200);
			_delay_ms(640); //This was 640ms
		}
		
		else if(Right_Disatance > Left_Distance)
		{
			Right(200);
			_delay_ms(640);
		}
}

void Measure_Distance()
{
	i = 0;
	while (i < 30)
	{
		/*** Center ***/
		ServoPosition(12);
		trig(timer);
		_delay_ms(20);
		Middle_Distance = distance;
		i++;
	}
	i = 0;
	
	while(i < 30)
	{
		/*** Left ***/
		ServoPosition(20);
		trig(timer);
		_delay_ms(20);
		Left_Distance = distance;
		i++;
	}
	i = 0;
	
	while (i < 30)
	{
		/*** Right ***/
		ServoPosition(4);
		trig(timer);
		_delay_ms(20);
		Right_Disatance = distance;
		i++;
	}
	i = 0;
}

void InitiateSensor()
{
	i = 0;
	while (i < 30)
	{
		/*** Center ***/
		ServoPosition(12);
		trig(timer);
		_delay_ms(1);
		Middle_Distance = distance;
		i++;
	}
	i = 0;
}

void Timer_Init()
{
	 	TIMSK0 |= (1 << TOIE0);
}

ISR(TIMER0_OVF_vect)
{
	stopwatch++;
	if (stopwatch == 7300)
	{
		Switch = 1;	
		stopwatch = 0;
		//You have this much timer to take over control.
		Stop();
		_delay_ms(5000);
	}
}

	

