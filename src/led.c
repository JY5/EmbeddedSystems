#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Define pins for each color channel of the RGB LED
#define RED_PIN 15
#define GREEN_PIN 16
#define BLUE_PIN 17

// Initialize the RGB LED on specified pins
void init_rgb_led() {
    gpio_set_function(RED_PIN, GPIO_FUNC_PWM);
    gpio_set_function(GREEN_PIN, GPIO_FUNC_PWM);
    gpio_set_function(BLUE_PIN, GPIO_FUNC_PWM);

    // Get PWM slice numbers for each color channel
    uint slice_red = pwm_gpio_to_slice_num(RED_PIN);
    uint slice_green = pwm_gpio_to_slice_num(GREEN_PIN);
    uint slice_blue = pwm_gpio_to_slice_num(BLUE_PIN);

    // Set PWM wrap to 255 for 8-bit control
    pwm_set_wrap(slice_red, 255);
    pwm_set_wrap(slice_green, 255);
    pwm_set_wrap(slice_blue, 255);

    // Enable PWM slices
    pwm_set_enabled(slice_red, true);
    pwm_set_enabled(slice_green, true);
    pwm_set_enabled(slice_blue, true);
}

// Set RGB LED color using PWM values (0-255 for each color channel)
void set_rgb_color(uint8_t red, uint8_t green, uint8_t blue) {
    pwm_set_gpio_level(RED_PIN, red);   // Red channel
    pwm_set_gpio_level(GREEN_PIN, green); // Green channel
    pwm_set_gpio_level(BLUE_PIN, blue);   // Blue channel
}
