#ifndef MICROPHONE_H
#define MICROPHONE_H

void init_microphone(uint gpio_pin);  // Accept GPIO pin as an argument
uint16_t get_audio_sample(void);

#endif // MICROPHONE_H
