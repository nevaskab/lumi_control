#include "pico/stdlib.h"
#include "matriz.h"
#include "hardware/pio.h"
#include "lumi_control.pio.h"

#define MATRIZ_PIN 7
#define MATRIZ_LEDS 25

static PIO pio = pio0;
static uint sm;

//inicializa a PIO da matriz de leds 5x5
void matriz_init(void) {
    sm = pio_claim_unused_sm(pio, true);
    uint offset = pio_add_program(pio, &lumi_control_program);
    lumi_control_program_init(pio, sm, offset, MATRIZ_PIN);
}

//função que será chamada quando necessário para apagar a matriz de leds
void matriz_clear(void) {
    uint32_t leds_off = 0x000000 << 8;
    uint32_t matriz_led_buffer[MATRIZ_LEDS];

    for(int i = 0; i < MATRIZ_LEDS; i++){
        matriz_led_buffer[i] = leds_off;
    }

    for (int i = 0; i < MATRIZ_LEDS; i++){
        pio_sm_put_blocking(pio, sm, matriz_led_buffer[i]);
    }
}

//Definindo a matriz de LEDs: em atividades anteriores, ao não definir a posição dos leds na matriz, há uma dificuldade em fazer os desenhos na mesma. Assim, seguindo o Hardware Data Base - Português, há esse mesmo mapa que pode ser usado para definir as posições de cada led, facilitando os desenhos.
static const uint8_t led_matriz[5][5] = {
    {24, 23, 22, 21, 20},
    {15, 16, 17, 18, 19},
    {14, 13, 12, 11, 10},
    {5,  6,  7,  8,  9},
    {4,  3,  2,  1,  0}
};
   
//Desenhos para cada número 
static const uint8_t matriz_numeros[10][MATRIZ_LEDS] = {
    //número 0
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 1
    {
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 2
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 3
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 4
    {
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0
    },
    //número 5
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 6
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 7
    {
    0.0, 1.0, 1.0, 1.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0
    },
    //número 8
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },
    //número 9
    {
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 1.0, 0.0
    },

};

//Configura a matriz de lds para ligar seguindo os desenhos da função acima, começa inicialmente desligada já que o desenho só aparecerá a medida que forem digitados números como entrada
void matriz_display_number(int numero_atual) {
    //cor do led tyrian purple
    uint32_t color = 0x400326;
    //leds desligados
    uint32_t leds_off = 0x000000 << 8;

    uint32_t matriz_led_buffer[MATRIZ_LEDS];
    for (int i = 0; i < MATRIZ_LEDS; i++) {
        matriz_led_buffer[i] = leds_off;
    }

    for (int num_rows = 0; num_rows < 5; num_rows++){
        for (int num_cols = 0; num_cols < 5; num_cols++){
            int led_index = num_rows * 5 + num_cols;
            if(matriz_numeros[numero_atual][led_index] == 1) {
                int led_index_placa = led_matriz[num_rows][num_cols];
                matriz_led_buffer[led_index_placa] = color;
            }
        }
    }

    for (int i = 0; i < MATRIZ_LEDS; i++){
        pio_sm_put_blocking(pio, sm, matriz_led_buffer[i]);
    }
}