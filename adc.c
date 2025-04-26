/*
 * adc.c
 *
 * Created: 06/12/2024 17.56.30
 * Author: rupesh majhi
 */ 

#include <avr/io.h>
#include "adc.h"

void ADC_init(void) {
	ADMUX = (1 << REFS0);                           // AVCC as reference
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, prescaler = 64
}

uint16_t ADC_read(void) {
	ADMUX = (ADMUX & 0xF8) | 0;  // Select ADC0 channel
	ADCSRA |= (1 << ADSC);       // Start conversion
	while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete
	return ADC;                  // Return ADC value
}

uint16_t adc_read_frequency(void) {
	uint16_t adc_value = ADC_read();
	return (adc_value * (1000 - 50) / 1023) + 50; // Scale ADC value to 50-1000 Hz
}
