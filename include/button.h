#ifndef BUTTON_H
#define BUTTON_H

#include "pico/stdlib.h"

// Initialize the button connected to the specified GPIO pin
void init_button(uint gpio);

// Check button state and detect press types
void check_button(uint gpio);

// Check if the button is pressed
bool is_button_pressed(uint gpio);

// Get the current tap count
int get_tap_count(void);

// Check if a long press is detected
bool is_long_press(void);

// Reset the tap count and long press state after processing
void reset_press_state(void); // Add this declaration

#endif
