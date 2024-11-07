#include "pico/stdlib.h"
#include <stdio.h>

// Define GPIO for the button
#define BUTTON_GPIO 14

// Define timing constants (in milliseconds)
#define DEBOUNCE_TIME 50
#define DOUBLE_TAP_TIME 250
#define TRIPLE_TAP_TIME 500
#define LONG_PRESS_TIME 1000

// Track button state and timing
bool button_pressed = false;
absolute_time_t last_press_time;
int tap_count = 0;

// Initialize the button with an internal pull-up resistor
void init_button() {
    gpio_init(BUTTON_GPIO);
    gpio_set_dir(BUTTON_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_GPIO);
}

// Function to check button state and detect press types
void check_button() {
    if (gpio_get(BUTTON_GPIO) == 0) {  // Button pressed (active-low)
        if (!button_pressed) {
            button_pressed = true;
            absolute_time_t now = get_absolute_time();

            // Calculate time since last press
            int64_t time_diff = absolute_time_diff_us(last_press_time, now) / 1000;
            last_press_time = now;

            // Ignore button noise
            if (time_diff < DEBOUNCE_TIME) return;

            // Detect long press
            if (time_diff > LONG_PRESS_TIME) {
                printf("Long press detected\n");
                tap_count = 0;  // Reset tap count after long press
            }
            // Detect double/triple taps
            else if (time_diff < DOUBLE_TAP_TIME) {
                tap_count++;
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
    } else {
        button_pressed = false;  // Reset button state on release
    }
}
