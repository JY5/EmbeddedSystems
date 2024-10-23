#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

// Initialize an LED connected to the specified GPIO pin
void init_led(uint gpio);

// Turn the LED on or off (true = on, false = off)
void set_led(uint gpio, bool state);

#endif
