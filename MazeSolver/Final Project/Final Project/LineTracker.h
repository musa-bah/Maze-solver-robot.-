int Switch;
void LineTrackerInit()
{
	sei();
	DDRD = ~(1 << PIND2);
	PCICR  |= (1 << PCIE2);
	PCMSK2 |= (PCINT20);
}

ISR(PCINT2_vect)
{
	if ( (PIND & (1 << PIND2)) || (PIND & (1 << PIND4)) )
	{
		Stop();
		_delay_ms(200);
		Switch = 1;
	}
}


