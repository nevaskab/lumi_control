#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "display.h"
#include "matriz.h"
#include "buttons.h"
#include "rgb_led.h"
#include "ssd1306.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define UART_TX_PIN 0
#define UART_RX_PIN 1

volatile int numero_atual = 0;

//Inicializa UART, SDA e SDL, além de inicializar botões, matriz, display e estabelecer uma mensagem inicial.
void setup_serial(){
    bool ok;

    ok = set_sys_clock_khz(128000, false);

    stdio_init_all();
    sleep_ms(10);

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    buttons_init();
    display_init();
    rgb_led_init();

    last_debounce_a_button = get_absolute_time();
    last_debounce_b_button = get_absolute_time();

    mensagem_led();
    strcpy(last_char, "Nenhum");
    display_clear();
    printf("Sistema inicializado. Aguardando comandos...\n");

    matriz_init();

    matriz_clear();
}

//Função que lê a entrada de caracteres e será chamada dentro do while(true) da função principal
void read_serial_input() {
    int c = getchar();
    
    if(c >= 32 && c < 127){
        printf("Caractere: %c\n", (char)c);
        
        sprintf(last_char, "Caractere: %c", (char)c);
        display_clear();

        if(isdigit(c)) {
            int numero_atual = c - '0';
            matriz_display_number(numero_atual);
        }
        else {
            //ao digitar algo que não seja um número, a matriz será desliagda
            matriz_clear();
        }
    }
    else {
        printf("Caractere Inválido.\n");
        display_clear();
    }
}

int main() {
    
    // Inicializações PIO
    setup_serial();

    //Função de interrupção sendo chamada para cada botão
    gpio_set_irq_enabled_with_callback(A_BUTTON, GPIO_IRQ_EDGE_FALL, true, &irq_button);
    gpio_set_irq_enabled_with_callback(B_BUTTON, GPIO_IRQ_EDGE_FALL, true, &irq_button);
    
    while (true) {
        read_serial_input();
    }
    return 0;
}