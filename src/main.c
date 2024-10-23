#include "pico/stdlib.h"
#include "mqtt.h"
#include "microphone.h"  // Include your microphone functions
#include <stdio.h>        // Required for printf

#define GREEN_LED_GPIO 15  // GPIO pin for the green LED
#define RED_LED_GPIO 16    // GPIO pin for the red LED
#define BUTTON_GPIO 14     // GPIO pin for the button
#define MIC_ADC_GPIO 26    // GPIO pin for microphone (ADC channel 0)

// Function to initialize GPIO pins
void init_gpio() {
    gpio_init(GREEN_LED_GPIO);
    gpio_set_dir(GREEN_LED_GPIO, GPIO_OUT);
    gpio_put(GREEN_LED_GPIO, false);  // Turn off green LED initially

    gpio_init(RED_LED_GPIO);
    gpio_set_dir(RED_LED_GPIO, GPIO_OUT);
    gpio_put(RED_LED_GPIO, false);    // Turn off red LED initially

    gpio_init(BUTTON_GPIO);
    gpio_set_dir(BUTTON_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_GPIO);  // Pull-up resistor for button
}

int main() {
    stdio_init_all();  // Initialize standard input/output for print statements

    // Initialize GPIO pins for LEDs, button, and microphone
    init_gpio();
    init_microphone(MIC_ADC_GPIO);  // Initialize microphone with GPIO pin

    // // Connect to Wi-Fi and MQTT broker
    // connect_wifi("your_SSID", "your_PASSWORD");  // Replace with actual Wi-Fi credentials
    // mqtt_connect();

    while (true) {
        // Check if the button is pressed (active-low)
        if (gpio_get(BUTTON_GPIO) == 0) {
            gpio_put(GREEN_LED_GPIO, true);  // Turn on green LED
            // mqtt_publish("button pressed");  // Send MQTT message
            sleep_ms(100);                   // Debounce delay

            // Wait until the button is released
            while (gpio_get(BUTTON_GPIO) == 0) {
                sleep_ms(100);  // Debounce delay
            }

            gpio_put(GREEN_LED_GPIO, false); // Turn off green LED when released
        }

        // Read and print an audio sample from the microphone
        uint16_t audio_sample = get_audio_sample();
        printf("Audio sample: %u\n", audio_sample);

        // // Check for MQTT messages (feedback)
        // mqtt_check_messages(GREEN_LED_GPIO, RED_LED_GPIO);

        // Add a delay to control the rate of microphone sampling and message checking
        sleep_ms(100);  // Adjust as needed to balance sampling and responsiveness
    }

    return 0;
}
