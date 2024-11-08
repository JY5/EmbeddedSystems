#include "pico/stdlib.h"
#include "led.h"
#include "button.h"
#include <stdio.h>

// Initialize GPIOs for the demo
void init_gpio() {
    init_rgb_led();
    init_button();
}

// Set LED color based on press type for testing
void set_led_color_based_on_press_type(int press_type) {
    switch (press_type) {
        case 1:
            set_rgb_color(255, 0, 0);    // Red for single tap
            break;
        case 2:
            set_rgb_color(0, 255, 0);    // Green for double tap
            break;
        case 3:
            set_rgb_color(0, 0, 255);    // Blue for triple tap
            break;
        case 4:
            set_rgb_color(128, 0, 128);  // Purple for long press
            break;
        default:
            set_rgb_color(0, 0, 0);      // Off for no press
            break;
    }
}

int main() {
    stdio_init_all();
    init_gpio();

    while (true) {
        check_button();  // Detect press types with debounce

        // Example logic to set LED based on tap count or long press
        if (tap_count == 1) {
            set_led_color_based_on_press_type(1);  // Single tap
        } else if (tap_count == 2) {
            set_led_color_based_on_press_type(2);  // Double tap
        } else if (tap_count == 3) {
            set_led_color_based_on_press_type(3);  // Triple tap
        } else if (is_long_press) {
            set_led_color_based_on_press_type(4);  // Long press
        }

        sleep_ms(100);  // Delay to control loop rate
    }
}
