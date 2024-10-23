#include "hardware/adc.h"

void init_microphone(uint gpio_pin) {
    adc_init();
    adc_gpio_init(gpio_pin);  // Initialize the specified GPIO pin for ADC
    adc_select_input(0);      // ADC channel 0 (corresponds to GPIO 26)
}

uint16_t get_audio_sample() {
    return adc_read();  // Return a 12-bit sample from the ADC
}
