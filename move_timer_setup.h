#ifndef _Move
#define _Move

#include <avr/io.h>
#include <avr/interrupt.h>

void MotorsInit()
{
	sei();
	DDRD = 0xFF;
	DDRB = 0xFF;
	
	TCCR0A = 0xA3;
	TCCR0B = 0x04;
	TCNT0 = 0x00;
}

void Forward(int duty)
{
	OCR0B = duty;
	OCR0A = duty;
	PORTD = 0b11100000;
	PORTB = 0b00001000;
}

void Backward(int duty)
{
	OCR0B = duty;
	OCR0A = duty;
	PORTD = 0b01100000;
	PORTB = 0b00000011;
}

void Stop()
{
	PORTD = 0b00000000;
	PORTB = 0b00000000;
}

void Left(int duty)
{
	OCR0B = duty;
	OCR0A = duty;
	PORTD = 0b01100000;
	PORTB = 0b00001001;
}

void Right(int duty)
{
	OCR0B = duty;
	OCR0A = duty;
	PORTD = 0b11100000;
	PORTB = 0b00000010;
}

void square_move()
{
	Forward(150);
	_delay_ms(1500);
	Stop();
	_delay_ms(500);
	Right(150);
	_delay_ms(650);
	Stop();
	_delay_ms(500);
	
	Forward(150);
	_delay_ms(1500);
	Stop();
	_delay_ms(500);
	Right(150);
	_delay_ms(650);
	Stop();
	_delay_ms(500);
	
	Forward(150);
	_delay_ms(1500);
	Stop();
	_delay_ms(500);
	Right(150);
	_delay_ms(650);
	Stop();
	_delay_ms(500);
	
	Forward(150);
	_delay_ms(1500);
	Stop();
	_delay_ms(500);
	Right(150);
	_delay_ms(650);
	Stop();
	_delay_ms(500);

}

void Circle_move(int i, int j)
{
	OCR0B = i;
	OCR0A = j;
	PORTD = 0b11100000;
	PORTB = 0b00001000;
}

void Lab_Demo()
{
	Forward(225);
	_delay_ms(2000);
	Stop();
	_delay_ms(500);
	Backward(127);
	_delay_ms(4000);
	Stop();
	_delay_ms(500);
	Left(225);
	_delay_ms(2000);
	Stop();
	_delay_ms(500);
	Right(127);
	_delay_ms(3000);
	Stop();
	_delay_ms(500);
}

#endif