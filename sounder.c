/*
 * sounder.c
 *
 * Created: 06/12/2024 17.55.38
 *  Author: Ghost Buster
 */ 
#define F_CPU 16000000UL // Define clock frequency as 16 MHz
#include <avr/io.h>
#include "sounder.h"
#include "main.h"

#define SOUNDER_PIN PINB1
#define FREQ_MIN 50     // Minimum frequency in Hz
#define FREQ_MAX 1000   // Maximum frequency in Hz

static uint16_t current_frequency = 440; // Default frequency

void sounder_init(void) {
	// Configure SOUNDER_PIN (PB1) as output
	DDRB |= (1 << SOUNDER_PIN);

	// Configure Timer1 for CTC mode
	TCCR1A = (1 << COM1A0);              // Toggle OC1A on Compare Match
	TCCR1B = (1 << WGM12) | (1 << CS11); // CTC Mode, Prescaler = 8
}

void sounder_set_frequency(uint16_t freq) {
	// Enforce frequency limits
	if (freq < FREQ_MIN) freq = FREQ_MIN;
	if (freq > FREQ_MAX) freq = FREQ_MAX;

	// Update Timer1 OCR1A for the given frequency
	OCR1A = (F_CPU / (2 * 8 * freq)) - 1;

	// Save the current frequency
	current_frequency = freq;
}

uint16_t sounder_get_frequency(void) {
	return current_frequency; // Return the currently set frequency
}
