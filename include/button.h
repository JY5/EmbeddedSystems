#ifndef BUTTON_H
#define BUTTON_H

#include "pico/stdlib.h"

// Initialize the button connected to the specified GPIO pin
void init_button(uint gpio);

// Check if the button is pressed
// Returns true if pressed, false otherwise
bool is_button_pressed(uint gpio);

#endif
