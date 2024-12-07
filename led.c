/*
 * led.c
 *
 * Created: 06/12/2024 17.55.23
 *  Author: Ghost Buster
 */ 

#include <avr/io.h>
#include "led.h"

#define LED_PIN PIND3

void led_init_pwm(void) {
	DDRD |= (1 << LED_PIN); // Configure LED_PIN as output
	TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1); // Fast PWM, non-inverting
	TCCR2B = (1 << CS21);  // Prescaler = 8
	OCR2B = 0;             // Start with 0 brightness
}

void led_set_brightness(uint8_t brightness) {
	OCR2B = brightness; // Set duty cycle (0-255)
}
