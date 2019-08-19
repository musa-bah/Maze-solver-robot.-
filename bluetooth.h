#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#define MY_BT_NAME "ROV42519"

#define F_CPU (16000000)
#define BAUDRATE (9600)
#define BAUD_PRESCALE (F_CPU/BAUDRATE/16 - 1)

#include <avr/io.h>

void uart_tx(char);
void uart_tx_str(char*);
char uart_rx();

void InitBluetooth()
{
	UBRR0H = (unsigned char)(BAUD_PRESCALE >> 8);
	UBRR0L = (unsigned char)BAUD_PRESCALE;
	UCSR0B = (1<<RXEN0)  | (1<<TXEN0);
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
	
	/* Set the BT name */
	uart_tx_str("AT+NAME=");
	uart_tx_str(MY_BT_NAME);
	uart_tx(0);
}

char receiveByte()
{
	return uart_rx();
}

void sendByte(char c)
{
	uart_tx(c);
}

void sendString(char* s)
{
	uart_tx_str(s);
}


/* write a byte to the UART */
void uart_tx(char c)
{
	/* busy-wait until UDRE0 in UCSR0A goes high */
	while ((UCSR0A & (1 << UDRE0)) == 0);
	/* then write the byte */
	UDR0 = c;
}

/* write a string to the UART, not including the null terminator */
void uart_tx_str(char* s)
{
	while (*s)
	uart_tx(*(s++));
}

/* return whatever byte is in the RX, if there is one. Return 0 otherwise */
char uart_rx()
{
	if (UCSR0A & (1 << RXC0))
	return UDR0;
	else
	return 0;
}

#endif /* BLUETOOTH_H_ */