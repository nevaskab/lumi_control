#ifndef BUTTONS_H
#define BUTTONS_H

#include "pico/stdlib.h"
#include <stdbool.h>

extern const uint A_BUTTON;
extern const uint B_BUTTON;
extern absolute_time_t last_debounce_a_button;
extern absolute_time_t last_debounce_b_button;

void buttons_init();
void irq_button(uint gpio, uint32_t events);

#endif // BUTTONS_H