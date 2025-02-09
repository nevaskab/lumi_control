#ifndef RGB_LED_H
#define RGB_LED_H

extern volatile bool green_led_state;
extern volatile bool blue_led_state;
extern char led_state[32];
void rgb_led_init();
void mensagem_led(void);
bool alternar_green_led();
bool alternar_blue_led();

#endif // RGB_LED_H