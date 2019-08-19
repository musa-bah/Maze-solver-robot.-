void ServoInit()
{
	/*** Enable global interrut ***/
	sei();
	
	/*** Set PD3 as output ***/
	DDRD |= (1 << PORTD3);
	
	/*** Timer setup for WGM 5, Non-Inverting mode, & 1024 prescaler ***/
	TCCR2A |= (1 << COM2B1) | (0 << COM2B0) | (0 << WGM21) | (1 << WGM20);
	TCCR2B |= (1 << WGM22)  | (1 << CS22)   | (1 << CS21)  | (1 << CS20);
	TCNT2 = 0x00;
	
	/*** Set the top value ***/
	//top_value = 16000000 / (2 * 1024 * 50);
	OCR2A = 156;
}

void ServoPosition(int angle)
{
	/*** Set the position ***/
	OCR2B = angle;
}
