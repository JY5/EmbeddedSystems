#include "pico/stdlib.h"
#include "led.h"       // Include RGB LED functions
#include "button.h"    // Include button functions
#include <stdio.h>

// GPIO pin definitions
#define BUTTON_GPIO 0

// Function to initialize GPIOs
void init_gpio() {
    init_rgb_led();     // Initialize RGB LED
    init_button(BUTTON_GPIO); // Pass the GPIO pin number
}

// Function to set the LED color based on button press type
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
    stdio_init_all();    // Initialize standard I/O for print statements

    // Initialize GPIO for RGB LED and button
    init_gpio();

    while (true) {
        // Call check_button to update tap count and long press state
        check_button(BUTTON_GPIO);

        // Detect different press types
        int press_type = 0; // Initialize press_type
        if (is_button_pressed(BUTTON_GPIO)) {
            // Check for single, double, triple tap, or long press
            if (get_tap_count() == 1) {
                press_type = 1; // Single tap
            } else if (get_tap_count() == 2) {
                press_type = 2; // Double tap
            } else if (get_tap_count() == 3) {
                press_type = 3; // Triple tap
            } else if (is_long_press()) {
                press_type = 4; // Long press
            }
        }

        // Set LED color based on press type
        set_led_color_based_on_press_type(press_type);

        // Delay for debounce and loop control
        sleep_ms(100);
    }

    return 0;
}

// #include "pico/stdlib.h"
// #include "led.h"       // Include RGB LED functions
// #include "button.h"    // Include button functions
// #include <stdio.h>

// // GPIO pin definitions
// #define BUTTON_GPIO 0

// // Function to initialize GPIOs
// void init_gpio() {
//     init_rgb_led();           // Initialize RGB LED
//     init_button(BUTTON_GPIO);  // Initialize button with the specified GPIO pin
// }

// // Function to set the LED color based on button press type
// void set_led_color_based_on_press_type(int press_type) {
//     switch (press_type) {
//         case 1:
//             set_rgb_color(255, 0, 0);    // Red for single tap
//             break;
//         case 2:
//             set_rgb_color(0, 255, 0);    // Green for double tap
//             break;
//         case 3:
//             set_rgb_color(0, 0, 255);    // Blue for triple tap
//             break;
//         case 4:
//             set_rgb_color(128, 0, 128);  // Purple for long press
//             break;
//         default:
//             set_rgb_color(0, 0, 0);      // Off for no press
//             break;
//     }
// }

// int main() {
//     stdio_init_all();    // Initialize standard I/O for print statements

//     // Initialize GPIO for RGB LED and button
//     init_gpio();

//     while (true) {
//         // Call check_button to update tap count and long press state
//         check_button(BUTTON_GPIO);

//         // Determine press type based on tap count and long press state
//         int press_type = 0; // Initialize press_type
//         if (is_button_pressed(BUTTON_GPIO)) {
//             if (is_long_press()) {
//                 press_type = 4; // Long press
//             } else if (get_tap_count() == 1) {
//                 press_type = 1; // Single tap
//             } else if (get_tap_count() == 2) {
//                 press_type = 2; // Double tap
//             } else if (get_tap_count() == 3) {
//                 press_type = 3; // Triple tap
//             }
//         }

//         // Set LED color based on the detected press type
//         set_led_color_based_on_press_type(press_type);

//         // Reset the press state after processing to prepare for the next detection
//         reset_press_state();

//         // Delay for debounce and loop control
//         sleep_ms(100);
//     }

//     return 0;
// }
