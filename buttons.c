#include <stdio.h>
#include "buttons.h"
#include "pico/stdlib.h"
#include "rgb_led.h"
#include "display.h"

#define NUM_BUTTONS 2
#define DEBOUNCE_DELAY 500

const uint A_BUTTON = 5;
const uint B_BUTTON = 6;

absolute_time_t last_debounce_a_button;
absolute_time_t last_debounce_b_button;

void buttons_init() {
    gpio_init(A_BUTTON);
    gpio_init(B_BUTTON);
    gpio_set_dir(A_BUTTON, GPIO_IN);
    gpio_set_dir(B_BUTTON, GPIO_IN);
    gpio_pull_up(A_BUTTON);
    gpio_pull_up(B_BUTTON);
}

//declarei os botões e uma variável com o último tempo para poder criar a função de debounce
const uint32_t gpio_button[NUM_BUTTONS] = {A_BUTTON, B_BUTTON};
uint32_t last_time[NUM_BUTTONS] = {0};

//a função de debounce vai analisar CADA UM dos botões e evitar que o botão tenha "trepidação" para não gerar erros de execução
bool debounce(uint gpio) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    int index_button = -1;

    for (int i = 0; i < NUM_BUTTONS; i++) {
        if (gpio_button[i] == gpio) {
            index_button = i;
            break;
        }
    }

    if (index_button == -1) {
        return false;
    }

    if (current_time - last_time[index_button] < DEBOUNCE_DELAY) {
        return false;
    }

    last_time[index_button] = current_time;
    return true;
}

//função de interrupção implementada juntamente com a ação de cada botão
//o botão A aciona o led verde
void irq_button(uint gpio, uint32_t events) {

    if(debounce(gpio)){

        if(gpio == A_BUTTON){
            bool estado = alternar_green_led(); //a variável 'estado' armazena o atual estado do led que será gerado na função alternar_green_led declarada em rgb_led.c

            mensagem_led(); //manda a mensagem pro display (função mensagem_led declarada em rgb_led.c)
            printf("LED Verde %s\n", estado ? "Ligado" : "Desligado");
            display_clear(); //atualiza o display a cada mudança de estado
        }
        //o botão B aciona o led azul
        else if(gpio == B_BUTTON){
            bool estado = alternar_blue_led(); //a variável 'estado' armazena o atual estado do led que será gerado na função alternar_blue_led declarada em rgb_led.c*

            mensagem_led();
            printf("LED Azul %s\n", estado ? "Ligado" : "Desligado");
            display_clear();
        }
    }
}