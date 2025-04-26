/*
 * switch.c
 *
 * Created: 06/12/2024 17.56.46
 * Author: rupesh majhi
 */ 

#include <avr/io.h>
#include <avr/sleep.h>
#include "switch.h"
#include <avr/interrupt.h>


#define SWITCH_PIN PIND2

void switch_init(void) {
	DDRD &= ~(1 << SWITCH_PIN); // Configure SWITCH_PIN as input
	PORTD |= (1 << SWITCH_PIN); // Enable internal pull-up resistor

	// Configure INT0 (External Interrupt 0)
	EICRA |= (1 << ISC01);    // Falling edge triggers interrupt
	EICRA &= ~(1 << ISC00);
	EIMSK |= (1 << INT0);     // Enable INT0 interrupt
}

void sleep_enter(void) {
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Configure power-down mode
	sleep_enable();
	sei(); // Ensure interrupts are enabled
	sleep_cpu(); // Enter sleep mode
	sleep_disable(); // Disable sleep after wake-up
}
