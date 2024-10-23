#include "pico/stdlib.h"

void init_button(uint gpio) {
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_IN);
    gpio_pull_up(gpio);
}

bool is_button_pressed(uint gpio) {
    return !gpio_get(gpio); // Returns true if button is pressed
}
