// 

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//Arquivo .pio
#include "animacao_MatrizLED.pio.h"

#define LED_PIN 0  // Pino de dados da matriz de LEDs
#define NUM_LEDS 25 // Total de LEDs na matriz 5x5

#define FPS 10 // Quadros por segundo

// Função para inicializar os LEDs
void init_leds() {
    ws2812_init(LED_PIN);
}

// Função para apagar todos os LEDs
void apagar_leds() {
    for (int i = 0; i < NUM_LEDS; i++) {
        ws2812_set_pixel(i, 0, 0, 0);
    }
    ws2812_show();
}

// Função para ligar todos os LEDs com uma cor
void ligar_todos_leds(uint8_t r, uint8_t g, uint8_t b) {
    for (int i = 0; i < NUM_LEDS; i++) {
        ws2812_set_pixel(i, r, g, b);
    }
    ws2812_show();
}

// Função principal
int main() {
    stdio_init_all();
    init_leds();

    printf("Iniciando controle da matriz de LEDs\n");

    while (true) {
        char tecla = keypad_get_key(); //Identifica a tecla pressionada

        switch (tecla) {
            case 'A':
                apagar_leds();
                break;
            case 'B':
                ligar_todos_leds(0, 0, 255);
                break;
            case 'C':
                ligar_todos_leds(204, 0, 0); // Vermelho com 80%
                break;
            case 'D':
                ligar_todos_leds(0, 128, 0); // Verde com 50%
                break;
            case '#':
                ligar_todos_leds(51, 51, 51); // Branco com 20%
                break;
            case '*':
                printf("Reiniciando o sistema...\n");
                watchdog_reboot(0, 0, 0); // Reboot
                break;
            default:
                printf("Tecla %c não atribuída.\n", tecla);
                break;
        }
        sleep_ms(100); // Debounce simples
    }
}