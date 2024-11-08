#include "pico/stdlib.h"
#include <stdio.h>

// Define GPIO for the button
#define BUTTON_GPIO 14

// Define timing constants (in milliseconds)
#define DEBOUNCE_TIME 50           // Minimum time between presses to avoid bounce
#define DOUBLE_TAP_TIME 250        // Max time between taps for a double tap
#define TRIPLE_TAP_TIME 500        // Max time between taps for a triple tap
#define LONG_PRESS_TIME 1000       // Time threshold for a long press

// Track button state and timing
bool button_pressed = false;
absolute_time_t last_press_time;
int tap_count = 0;
bool is_long_press = false;

// Initialize the button with an internal pull-up resistor
void init_button() {
    gpio_init(BUTTON_GPIO);
    gpio_set_dir(BUTTON_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_GPIO);
}

// Function to detect button press types with debouncing
void check_button() {
    static absolute_time_t debounce_time = {0};

    // Check if button is pressed (active-low)
    if (gpio_get(BUTTON_GPIO) == 0) {
        if (!button_pressed && absolute_time_diff_us(debounce_time, get_absolute_time()) > DEBOUNCE_TIME * 1000) {
            button_pressed = true;
            debounce_time = get_absolute_time(); // Reset debounce timer

            // Capture time of this press
            absolute_time_t now = get_absolute_time();
            int64_t time_diff = absolute_time_diff_us(last_press_time, now) / 1000; // Convert to ms
            last_press_time = now;

            // Detect press type based on time differences
            if (time_diff > LONG_PRESS_TIME) {
                printf("Long press detected\n");
                is_long_press = true;
                tap_count = 0;  // Reset tap count for long press
            } else if (time_diff < DOUBLE_TAP_TIME) {
                tap_count++;
                is_long_press = false;  // Reset long press flag

                if (tap_count == 2) {
                    printf("Double tap detected\n");
                } else if (tap_count == 3) {
                    printf("Triple tap detected\n");
                    tap_count = 0;  // Reset after triple tap
                }
            } else {
                printf("Single tap detected\n");
                tap_count = 1;
            }
        }
    } else if (button_pressed) {
        button_pressed = false;  // Button was released
    }
}
