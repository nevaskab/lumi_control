#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "rgb_led.h"
#include "pico/stdlib.h"
#include "display.h"

#define LED_RGB_GREEN 11
#define LED_RGB_BLUE 12

volatile bool green_led_state = false;
volatile bool blue_led_state = false;

char led_state[32] = "Leds desligados";

//inicializa os leds verde e azul
void rgb_led_init() {
    gpio_init(LED_RGB_GREEN);
    gpio_init(LED_RGB_BLUE);
    gpio_set_dir(LED_RGB_GREEN, GPIO_OUT);
    gpio_set_dir(LED_RGB_BLUE, GPIO_OUT);
}

//função para alterar as mensagens do display baseado no estado do led
void mensagem_led(void){
    if (green_led_state && blue_led_state){
        strcpy(led_state, "Led Verde e Azul: ON");
    }
    else if (green_led_state){
        strcpy(led_state, "Led Verde: ON");
    }
    else if (blue_led_state){
        strcpy(led_state, "Led Azul: ON");
    }
    else {
        strcpy(led_state, "Led Verde e Azul: OFF");
    }
}

//função para alterar o estado dos leds e retorna o estado atual para a variável
//led verde
bool alternar_green_led() {
    green_led_state = !green_led_state;
    gpio_put(LED_RGB_GREEN, green_led_state);

    return green_led_state;
}

//led azul
bool alternar_blue_led() {
    blue_led_state = !blue_led_state;
    gpio_put(LED_RGB_BLUE, blue_led_state);

    return blue_led_state;
}