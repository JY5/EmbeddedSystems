#ifndef MICROPHONE_H
#define MICROPHONE_H

#include "pico/stdlib.h"

// Initialize the microphone connected to the ADC pin
void init_microphone(void);

// Get a sample from the microphone (16-bit ADC value)
uint16_t get_audio_sample(void);

#endif
