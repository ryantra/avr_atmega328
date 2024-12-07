/*
 * usart.h
 *
 * Created: 06/12/2024 17.54.47
 *  Author: Ghost Buster
 */ 


#ifndef USART_H_
#define USART_H_


#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#ifndef F_CPU
#define F_CPU 16000000UL // Set the clock frequency to 16 MHz
#endif


// USART Configuration
#define BAUDRATE 9600ul
#define UBRRVALUE (F_CPU / (16ul * BAUDRATE) - 1)

// Function Prototypes
void USART_init(void);                         // Initialize USART
void USART_sendString(const char *str);        // Send a null-terminated string
void handle_usart_commands(volatile uint16_t *frequency, volatile uint8_t *frequency_override);
char USART_readCommand(void);



#endif /* USART_H_ */