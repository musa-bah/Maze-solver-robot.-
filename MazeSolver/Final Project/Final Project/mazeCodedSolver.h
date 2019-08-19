#ifndef MAZECODEDSOLVER_H_
#define MAZECODEDSOLVER_H_

#include <avr/io.h>
#include <util/delay.h>
#include "bluetooth.h"
#include "Ultrasonic.h"
#include "motor_control.h"

void marchForward()
{
	InitUltrasonic();
	timer = 200;
	duty = 200;
	count = 200;
	
	while(1)
	{
		double distFront = 255;
		trig();
		distance_cm(timer);
		distFront = count;
		
		forward(255);
		_delay_ms(50);
		stop();
		
		if(distFront < 25 && distFront > 1)
		break;
	}
	
	return;
	
}

void mazeLeft()
{
	int delayTime = 50;
	int delayTime2 = 100;
	int turnSpeed = 200;
	int turnNumber = 15;
	int moveNumber = 12;

	for(int i = 0; i < turnNumber; i++)
	{
		left(turnSpeed); // motor control
		_delay_ms(delayTime);
		stop();
	}
	
	_delay_ms(delayTime2);
	marchForward();
	_delay_ms(delayTime2);
	
	for(int i = 0; i < turnNumber; i++)
	{
		right(turnSpeed); // motor control
		_delay_ms(delayTime);
		stop();
	}
	
	_delay_ms(delayTime2);
	marchForward();
	_delay_ms(delayTime2);

	for(int i = 0; i < turnNumber; i++)
	{
		right(turnSpeed); // motor control
		_delay_ms(delayTime);
		stop();
	}
	
	for(int i = 0; i < moveNumber; i++)
	{
		forward(255);
		_delay_ms(50);
		stop();
	}
	
	for(int i = 0; i < turnNumber; i++)
	{
		left(turnSpeed); // motor control
		_delay_ms(delayTime);
		stop();
	}
	
	for(int i = 0; i < 6; i++)
	{
		forward(255);
		_delay_ms(50);
		stop();
	}
	
	return;
	
	
}

void mazeRight()
{
	int delayTime = 50;
	int delayTime2 = 100;
	int turnSpeed = 200;
	int turnNumber = 15;
	int moveNumber = 12;

	for(int i = 0; i < turnNumber; i++)
	{
		right(turnSpeed); // motor control
		_delay_ms(delayTime);
		stop();
	}
	
	_delay_ms(delayTime2);
	marchForward();
	_delay_ms(delayTime2);
	
	for(int i = 0; i < turnNumber; i++)
	{
		left(turnSpeed); // motor control
		_delay_ms(delayTime);
		stop();
	}
	
	_delay_ms(delayTime2);
	marchForward();
	_delay_ms(delayTime2);

	for(int i = 0; i < turnNumber; i++)
	{
		right(turnSpeed); // motor control
		_delay_ms(delayTime);
		stop();
	}
	
	for(int i = 0; i < moveNumber; i++)
	{
		forward(255);
		_delay_ms(50);
		stop();
	}
	
	for(int i = 0; i < turnNumber; i++)
	{
		right(turnSpeed); // motor control
		_delay_ms(delayTime);
		stop();
	}
	
	for(int i = 0; i < 6; i++)
	{
		forward(255);
		_delay_ms(50);
		stop();
	}
	
	return;
	
	
}

#endif /* MAZECODEDSOLVER_H_ */