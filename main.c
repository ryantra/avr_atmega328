/*
 * Microcontroller_Final.c
 *
 * Created: 06/12/2024 17.54.08
 * Author : Manisha
 */ 

#include "main.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <string.h>
#include "usart.h"
#include "led.h"
#include "adc.h"
#include "switch.h"
#include "sounder.h"

volatile uint8_t system_active = 1; // 1 = Active, 0 = Inactive
volatile uint16_t frequency = 440;  // Default frequency
volatile uint8_t frequency_override = 0; // 1 = Use Virtual Terminal frequency, 0 = Use ADC


int main(void) {
	led_init_pwm();        // Initialize LED with PWM
	switch_init();         // Initialize on/off switch
	USART_init();          // Initialize USART for communication
	ADC_init();            // Initialize ADC for potentiometer
	sounder_init();        // Initialize sounder

	sei(); // Enable global interrupts

	USART_sendString("System initialized. Waiting for commands...\r\n");

	uint16_t counter = 0;     // Counter for 2-second timer
	uint8_t brightness = 0;   // PWM brightness level
	uint8_t increasing = 1;   // Flag for brightness direction

	while (1) {
		if (!system_active) {
			USART_sendString("System is inactive. Entering low-power mode.\r\n");
			sleep_enter();
		}

		// Handle USART commands
		handle_usart_commands(&frequency, &frequency_override);

		// Adjust LED brightness smoothly
		if (increasing) {
			brightness++;
			if (brightness == 255) increasing = 0; // Reverse direction
			} else {
			brightness--;
			if (brightness == 0) increasing = 1;  // Reverse direction
		}
		led_set_brightness(brightness);
		_delay_ms(10);

		if (!frequency_override) {
			// Update frequency from potentiometer
			frequency = adc_read_frequency();
		}

		// Update the sounder's frequency
		sounder_set_frequency(frequency);

		// Send frequency to Virtual Terminal every 2 seconds
		counter += 10; // Increment by LED delay (10 ms)
		if (counter >= 2000) {
			char buffer[30];
			sprintf(buffer, "Frequency is %d Hz\r\n", sounder_get_frequency());
			USART_sendString(buffer);
			counter = 0; // Reset the counter
		}
	}
}

ISR(INT0_vect) {
	_delay_ms(50); // Simple debounce
	system_active = !system_active; // Toggle system state
	if (system_active) {
		USART_sendString("System is now active.\r\n");
		} else {
		USART_sendString("System is now inactive.\r\n");
	}

	EIFR |= (1 << INTF0); // Clear the external interrupt flag
}
