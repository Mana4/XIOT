#include "micro_config.h"

#define NUMBER_OF_OVERFLOWS_PER_THREE_SECOND 12

unsigned char g_tick = 0;
extern str[20]; // store temperature as string to send it
ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if(g_tick >= NUMBER_OF_OVERFLOWS_PER_THREE_SECOND)
	{
		UART_sendString(str);
		//UART_sendByte(g_tick);
		g_tick = 0; //clear the tick counter again to count a new 3.1 second
	}

}

/* Description : 
 * For clock=1Mhz and prescale F_CPU/1024 every count will take 1ms
 * so put initial timer counter=0  0 --> 255 (256ms per overflow)
 * so we need timer to overflow 12 times to get a 3.1 second
 */
void timer0_init_normal_mode(void)
{
	SREG  &= ~(1<<7);      // Disable interrupts by clearing I-bit
	TCNT0 = 0; //timer initial value
	TIMSK |= (1<<TOIE0); //enable overflow interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0 
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
	SREG  |= (1<<7); //enable global interrupts in MC by setting the I-Bit.
}

