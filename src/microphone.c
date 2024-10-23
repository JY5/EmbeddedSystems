#include "hardware/adc.h"

void init_microphone() {
    adc_init();
    adc_gpio_init(26);  // Assuming microphone is connected to GPIO 26
    adc_select_input(0); // ADC channel 0
}

uint16_t get_audio_sample() {
    return adc_read();  // Returns a sample of the microphone input
}
