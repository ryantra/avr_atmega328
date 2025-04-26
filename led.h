/*
 * led.h
 *
 * Created: 06/12/2024 17.55.08
 * Author: rupesh majhi
 */ 


#ifndef LED_H_
#define LED_H_

#include <stdint.h>

void led_init_pwm(void);
void led_set_brightness(uint8_t brightness);



#endif /* LED_H_ */
