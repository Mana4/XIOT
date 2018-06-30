/*
 * Main.c
 *
 *  Created on: Jun 24, 2018
 *      Author: Mana
 */
#include "micro_config.h"

volatile unsigned char g_Button;

/* External INT0 Interrupt Service Routine */
ISR(INT1_vect) {
	g_Button = 1;

}


void INT1_Init(void)
{
	SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	PORTD &= (~(1<<PD3));     // Enable the internal pull up resistor at PD3 pin
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
	// Trigger INT1 with the falling edge
	MCUCR |= (1<<ISC11);
	MCUCR &= ~(1<<ISC10);
	SREG  |= (1<<7);       // Enable interrupts by setting I-bit
}


char str[20];

int main() {



     float temp;

	//led configuration
	DDRC = DDRC | (1 << PC0);  // Configure pin PC0 in PORTC as output pin
	PORTC = PORTC & (~(1<<PC0)); // Initialization Led is off at the beginning

	 unsigned char sw_Status[] = "\rSWITCH Pressed\r";
	 unsigned char led_Status[2][12] =
	{
			{"\rLED ON\r"} ,
			{"\rLED OFF\r"}
		};
	//unsigned char led_Status[2];

    INT1_Init();       // Enable external INT0

    ADC_init(); /* initialize ADC driver */
    timer0_init_normal_mode();	//start the timer.

    /// UART INITIALLIZTAION
	UART_init();

	g_Button = 0;
	while (1)
	{


		if (g_Button == 1) {

			PORTC = PORTC ^ (1 << PC0); //toggle led state


			UART_sendString(sw_Status);
           if(PINC & 1)
        	   UART_sendString(led_Status[0]);
           else
        	   UART_sendString(led_Status[1]);
			g_Button = 0;
		}
		temp = ADC_read(0);
		temp = (temp*150*5)/(1023*1.5);  //Determine temperature from adc read value
       sprintf(str,"\rtem =%d \r",(int)temp);

	}

	return 0;
}

