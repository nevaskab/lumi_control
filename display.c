#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "rgb_led.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_ADDRESS 0x3C
#define I2C_PORT i2c1 //a placa bitdoglab utiliza o canal I2C1 por padrão
#define SDA_PIN 14
#define SCL_PIN 15

//declaração da estrutura ssd1306_t
ssd1306_t ssd;

char last_char[32] = "Caractere: ";

//função que inicializa o display
void display_init() {
    //configura o I2C (display)
    i2c_init(I2C_PORT, 100 * 1000);  // 100 kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Inicializa o display ssd
    ssd1306_init(&ssd, DISPLAY_WIDTH, DISPLAY_HEIGHT, false, DISPLAY_ADDRESS, I2C_PORT);
    ssd1306_fill(&ssd, false);
    ssd1306_config(&ssd);
}

// Limpa o display
void display_clear(void) {
    //limpa o buffer definindo todos os pixels como 0
    ssd1306_fill(&ssd, 0); 
    //começa o desenho doe estado dos leds na linha 0  coluna 0
    ssd1306_draw_string(&ssd, led_state, 0, 0);
    //começa o desenho do caractere na coluna 25
    ssd1306_draw_string(&ssd, last_char, 0, 25);
    //atualiza o display
    ssd1306_send_data(&ssd);
}

