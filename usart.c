/*
 * usart.c
 *
 * Created: 06/12/2024 17.54.29
 *  Author: Ghost Buster
 */ 

#include "usart.h"
#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void USART_init(void) {
	UBRR0H = (unsigned char)(103 >> 8); // Assuming 9600 baud rate
	UBRR0L = (unsigned char)103;

	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Enable receiver and transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 data bits, 1 stop bit
}

void USART_sendString(const char *str) {
	while (*str) {
		while (!(UCSR0A & (1 << UDRE0))); // Wait for the transmit buffer to be empty
		UDR0 = *str++;                   // Send the character
	}
}

char USART_readCommand(void) {
	if (UCSR0A & (1 << RXC0)) { // Check if data is available
		return UDR0;           // Return received data
	}
	return 0; // No data received
}

void handle_usart_commands(volatile uint16_t *frequency, volatile uint8_t *frequency_override) {
	static char input_buffer[10] = "";
	static uint8_t buffer_index = 0;
	char command = USART_readCommand();

	if (command) {
		if (command == '+') {
			if (*frequency < 1000) (*frequency) += 10;
			USART_sendString("Increased frequency by 10 Hz\r\n");
			*frequency_override = 1;
			} else if (command == '-') {
			if (*frequency > 50) (*frequency) -= 10;
			USART_sendString("Decreased frequency by 10 Hz\r\n");
			*frequency_override = 1;
			} else if (command >= '0' && command <= '9') {
			if (buffer_index < sizeof(input_buffer) - 1) {
				input_buffer[buffer_index++] = command;
				input_buffer[buffer_index] = '\0';
			}
			} else if (command == '\r') {
			if (buffer_index > 0) {
				uint16_t new_frequency = atoi(input_buffer);
				if (new_frequency >= 50 && new_frequency <= 1000) {
					*frequency = new_frequency;
					*frequency_override = 1;
					USART_sendString("Frequency set to ");
					char freq_msg[20];
					sprintf(freq_msg, "%d Hz\r\n", new_frequency);
					USART_sendString(freq_msg);
					} else {
					USART_sendString("Invalid frequency. Must be 50-1000 Hz.\r\n");
				}
				buffer_index = 0;
				input_buffer[0] = '\0';
			}
			} else {
			USART_sendString("Unknown command\r\n");
		}
	}
}