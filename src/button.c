#include "pico/stdlib.h"
#include <stdio.h>
#include "button.h"

// Define timing constants (in milliseconds)
#define DEBOUNCE_TIME 50
#define LONG_PRESS_TIME 1000

// Track button state and timing
static bool button_pressed = false;
static absolute_time_t last_press_time;
static int tap_count = 0;
static bool long_press_detected = false; // Track long press state

// Initialize the button with an internal pull-up resistor
void init_button(uint gpio) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
    gpio_pull_up(gpio);
}

// Function to check button state and detect press types
void check_button(uint gpio) {
    if (gpio_get(gpio) == 0) {  // Button pressed (active-low)
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
                long_press_detected = true;
                tap_count = 0;  // Reset tap count after long press
            } else {
                tap_count++;
                long_press_detected = false; // Reset long press
            }
        }
    } else {
        button_pressed = false;  // Reset button state on release
    }
}

// Function to check if the button is pressed
bool is_button_pressed(uint gpio) {
    return (gpio_get(gpio) == 0); // Return true if button is pressed (active-low)
}

// Get the current tap count
int get_tap_count(void) {
    return tap_count; // Return current tap count
}

// Check if a long press is detected
bool is_long_press(void) {
    return long_press_detected; // Return long press state
}

// #include "pico/stdlib.h"
// #include <stdio.h>
// #include "button.h"

// // Define timing constants (in milliseconds)
// #define DEBOUNCE_TIME 50
// #define LONG_PRESS_TIME 1000

// // Track button state and timing
// static bool button_pressed = false;
// static absolute_time_t last_press_time;
// static int tap_count = 0;
// static bool long_press_detected = false; // Track long press state

// // Initialize the button with an internal pull-up resistor
// void init_button(uint gpio) {
//     gpio_init(gpio);
//     gpio_set_dir(gpio, GPIO_IN);
//     gpio_pull_up(gpio);
// }

// // Function to check button state and detect press types
// void check_button(uint gpio) {
//     if (gpio_get(gpio) == 0) {  // Button pressed (active-low)
//         if (!button_pressed) {
//             button_pressed = true;
//             absolute_time_t now = get_absolute_time();

//             // Calculate time since last press
//             int64_t time_diff = absolute_time_diff_us(last_press_time, now) / 1000;
//             last_press_time = now;

//             // Ignore button noise
//             if (time_diff < DEBOUNCE_TIME) return;

//             // Detect long press
//             if (time_diff > LONG_PRESS_TIME) {
//                 long_press_detected = true;
//                 tap_count = 0;  // Reset tap count after long press
//             } else {
//                 tap_count++; // Increment tap count for normal taps
//                 long_press_detected = false; // Reset long press
//             }
//         }
//     } else {
//         if (button_pressed) {
//             // Reset button state on release
//             button_pressed = false;
//         }
//     }
// }

// // Function to check if the button is currently pressed
// bool is_button_pressed(uint gpio) {
//     return (gpio_get(gpio) == 0); // Return true if button is pressed (active-low)
// }

// // Function to get the current tap count
// int get_tap_count(void) {
//     return tap_count; // Return the current tap count
// }

// // Function to check if a long press is detected
// bool is_long_press(void) {
//     return long_press_detected; // Return true if a long press was detected
// }

// // Function to reset the tap count and long press state after processing
// void reset_press_state(void) {
//     tap_count = 0;
//     long_press_detected = false;
// }
