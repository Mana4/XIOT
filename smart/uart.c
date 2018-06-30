/*
 * UART.c
 *
 * Created: 2/19/2014 8:07:58 PM
 * Author: Mohamed Tarek
 */

#include "micro_config.h"

void UART_init(void)
{
	// U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);
	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/ 
	UCSRB = (1<<RXEN) | (1<<TXEN);
	
	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/ 	
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	
	/* baud rate=9600 & Fosc=1MHz -->  UBBR=( Fosc / (8 * baud rate) ) - 1 = 12 */
	UBRRH = 0;
	UBRRL = 12;
 }


void UART_sendByte(const unsigned char data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for 
	 * transmitting a new byte so wait until this flag is set to one */
	while(!(UCSRA & (1<<UDRE))){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as 
	 * the UDR register is not empty now */	 
	UDR = data;
}



void UART_sendString(const unsigned char *Str)
{
	unsigned char i = 0;
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}

}


