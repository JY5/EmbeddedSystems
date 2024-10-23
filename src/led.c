#include "pico/stdlib.h"

void init_led(uint gpio) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
}

void set_led(uint gpio, bool state) {
    gpio_put(gpio, state);
}
