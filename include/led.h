#ifndef LED_H
#define LED_H

#include "pico/stdlib.h"

// Initialize RGB LED
void init_rgb_led(void); // Declare init_rgb_led

// Set RGB LED color
void set_rgb_color(uint8_t red, uint8_t green, uint8_t blue); // Declare set_rgb_color

#endif
