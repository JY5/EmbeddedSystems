#include "pico/stdlib.h"
#include "led.h"
#include "button.h"
#include "microphone.h"  // Include microphone functions
#include <stdio.h>

// Function to initialize GPIO for RGB LED and button
void init_gpio() {
    init_rgb_led();  // Initialize RGB LED pins
    init_button();   // Initialize button with advanced detection
}

int main() {
    stdio_init_all();      // Initialize standard input/output

    // Initialize GPIO for LEDs and button
    init_gpio();
    init_microphone(26);   // Initialize microphone on GPIO 26

    while (true) {
        // Check for button press types
        check_button();

        // Set LED color based on button press types (examples)
        if (is_button_pressed(BUTTON_GPIO)) {
            set_rgb_color(128, 0, 128);  // Purple for initial button press
        } else {
            set_rgb_color(0, 0, 0);  // Turn off LED when button is not pressed
        }

        // Read and print audio sample from microphone
        uint16_t audio_sample = get_audio_sample();
        printf("Audio sample: %u\n", audio_sample);

        sleep_ms(100);  // Adjust delay as needed
    }

    return 0;
}
