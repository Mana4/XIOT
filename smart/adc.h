/*
 * adc.h
 *
 *  Created on: Jun 27, 2018
 *      Author: Mana
 */

#ifndef ADC_H_
#define ADC_H_

#include "micro_config.h"

extern unsigned int data;

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(void);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
unsigned int ADC_read(unsigned char channel_num);

#endif /* ADC_H_ */
