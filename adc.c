/*
 * adc.c
 *
 *  Created on: Jun 27, 2018
 *      Author: Mana
 */

#include "adc.h"

void ADC_init(void)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0;

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=8Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1);
}

unsigned int ADC_read(unsigned char channel_num)
{
	channel_num &= 0x07; /* channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* choose the correct channel by setting the channel number in MUX4:0 bits */
	ADCSRA|=(1<<ADSC); /* start conversion write '1' to ADSC */
	while(!(ADCSRA & (1<<ADIF))); /* wait for conversion to complete ADIF becomes '1' */

	ADCSRA|=(1<<ADIF); /* clear ADIF by write '1' to it :) */
	return ADC; /* return the data register */
}
