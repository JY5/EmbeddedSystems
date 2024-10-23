#include "pico/stdlib.h"
#include "button.h"
#include "led.h"
#include "microphone.h"
// #include "mqtt.h"

int main() {
    stdio_init_all();

    // Initialize components
    init_button(14);  // Button connected to GPIO 14
    init_led(15);     // Green LED on GPIO 15
    init_led(16);     // Red LED on GPIO 16
    init_microphone();

    // connect_wifi("SSID", "PASSWORD");

    while (true) {
        if (is_button_pressed(14)) {
            set_led(15, true);  // Turn on the green LED when the button is pressed
        } else {
            set_led(15, false); // Turn off the LED when the button is not pressed
        }

        sleep_ms(10);  // Short delay to avoid excessive CPU usage
    }
}
