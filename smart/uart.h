/*
 * UART.h
 *
 * Created: 2/19/2014 8:08:52 PM
 * Author: Mohamed Tarek
 */  

#ifndef UART_H_
#define UART_H_

#include "micro_config.h"

void UART_init(void);

void UART_sendByte(const unsigned char data);

void UART_sendString(const unsigned char *Str);

#endif /* UART_H_ */
