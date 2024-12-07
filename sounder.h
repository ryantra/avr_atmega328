/*
 * sounder.h
 *
 * Created: 06/12/2024 17.55.58
 *  Author: Ghost Buster
 */ 


#ifndef SOUNDER_H_
#define SOUNDER_H_

#include <stdint.h>

// Initialize the sounder
void sounder_init(void);

// Set the sounder frequency (in Hz)
void sounder_set_frequency(uint16_t freq);

// Get the current sounder frequency
uint16_t sounder_get_frequency(void);



#endif /* SOUNDER_H_ */