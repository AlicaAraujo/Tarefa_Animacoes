#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "hardware/adc.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "animacao_MatrizLED.pio.h"

// Configurações gerais
#define NUM_PIXELS 25
#define OUT_PIN 7

// Teclado matricial
#define TECLADO_PIN_1 28
#define TECLADO_PIN_2 27
#define TECLADO_PIN_3 26
#define TECLADO_PIN_4 22
#define COL1_PIN 21
#define COL2_PIN 20
#define COL3_PIN 19
#define COL4_PIN 18

// Templates
void animacao_1(PIO pio, uint sm, int fps);
void animacao_2(PIO pio, uint sm, int fps);
void animacao_3(PIO pio, uint sm, int fps);
void animacao_4(PIO pio, uint sm, int fps);
void animacao_5(PIO pio, uint sm, int fps);
void animacao_6(PIO pio, uint sm, int fps);
void animacao_7(PIO pio, uint sm, int fps);

// Calcula a cor RGB para os LEDs
// Parâmetros:
// - b: Intensidade da cor azul (0.0 a 1.0)
// - r: Intensidade da cor vermelha (0.0 a 1.0)
// - g: Intensidade da cor verde (0.0 a 1.0)
uint32_t calcular_cor_rgb(double b, double r, double g) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Configura todos os LEDs para uma cor específica
// Parâmetros:
// - pio: Instância do bloco PIO
// - sm: Máquina de estado usada para o controle
// - r: Intensidade da cor vermelha (0.0 a 1.0)
// - g: Intensidade da cor verde (0.0 a 1.0)
// - b: Intensidade da cor azul (0.0 a 1.0)
void configurar_todos_leds(PIO pio, uint sm, double r, double g, double b) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        uint32_t color = calcular_cor_rgb(b, r, g);
        pio_sm_put_blocking(pio, sm, color);
    }
}

// Configura a GPIO e inicializa a PIO para controlar os LEDs
// Parâmetros:
// - pio: Instância do bloco PIO
// - sm: Ponteiro para a máquina de estado
// - pin: GPIO conectado à matriz de LEDs
void configurar_gpio_pio(PIO pio, uint *sm, uint pin) {
    uint offset = pio_add_program(pio, &animacao_MatrizLED_program);
    *sm = pio_claim_unused_sm(pio, true);
    animacao_MatrizLED_program_init(pio, *sm, offset, pin);
}

// Configura os pinos para o teclado matricial
// Inicializa as linhas como saída e as colunas como entrada
void configurar_teclado() {
    // Configurar pinos das linhas como saída
    gpio_init(TECLADO_PIN_1);
    gpio_init(TECLADO_PIN_2);
    gpio_init(TECLADO_PIN_3);
    gpio_init(TECLADO_PIN_4);

    gpio_set_dir(TECLADO_PIN_1, GPIO_OUT);
    gpio_set_dir(TECLADO_PIN_2, GPIO_OUT);
    gpio_set_dir(TECLADO_PIN_3, GPIO_OUT);
    gpio_set_dir(TECLADO_PIN_4, GPIO_OUT);

    // Configurar pinos das colunas como entrada
    gpio_init(COL1_PIN);
    gpio_init(COL2_PIN);
    gpio_init(COL3_PIN);
    gpio_init(COL4_PIN);

    gpio_set_dir(COL1_PIN, GPIO_IN);
    gpio_set_dir(COL2_PIN, GPIO_IN);
    gpio_set_dir(COL3_PIN, GPIO_IN);
    gpio_set_dir(COL4_PIN, GPIO_IN);

    gpio_pull_down(COL1_PIN);
    gpio_pull_down(COL2_PIN);
    gpio_pull_down(COL3_PIN);
    gpio_pull_down(COL4_PIN);
}

// Verifica qual tecla do teclado matricial foi pressionada
// Retorna:
// - Caractere correspondente à tecla pressionada
// - 0 se nenhuma tecla foi pressionada
char verificar_teclado() {
    const char keys[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};

    for (int row = 0; row < 4; row++) {
        gpio_put(TECLADO_PIN_1, row == 0);
        gpio_put(TECLADO_PIN_2, row == 1);
        gpio_put(TECLADO_PIN_3, row == 2);
        gpio_put(TECLADO_PIN_4, row == 3);

        sleep_us(10); // Tempo para estabilizar

        if (gpio_get(COL1_PIN)) return keys[row][0];
        if (gpio_get(COL2_PIN)) return keys[row][1];
        if (gpio_get(COL3_PIN)) return keys[row][2];
        if (gpio_get(COL4_PIN)) return keys[row][3];
    }

    return 0; // Nenhuma tecla pressionada
}

// Animações
// Executa a animação 1: alternância entre vermelho e verde
// Parâmetros:
// - pio: Instância do bloco PIO
// - sm: Máquina de estado usada para o controle
// - fps: Taxa de quadros por segundo da animação
void animacao_1(PIO pio, uint sm, int fps) {
    for (int frame = 0; frame < 5; frame++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            uint32_t color = (frame % 2 == 0) ? calcular_cor_rgb(0.5, 0.0, 0.0) : calcular_cor_rgb(0.0, 0.5, 0.0);
            pio_sm_put_blocking(pio, sm, color);
        }
        sleep_ms(1000 / fps);
    }
}

// Animações
// Executa a animação 3: alternância entre  as letras D(azul), A(amarelo), V(roxo), I(verde) e D(vermelho)
// Parâmetros:
// - pio: Instância do bloco PIO
// - sm: Máquina de estado usada para o controle
// - fps: Taxa de quadros por segundo da animação
void animacao_3(PIO pio, uint sm, int fps) { 
    for (int frame = 0; frame < 5; frame++) {
        uint32_t color2 = calcular_cor_rgb(0.0, 0.0, 0.0);
        
        if (frame == 0)
        {
            for (int i = 0; i < NUM_PIXELS; i++) {
                uint32_t color1 = calcular_cor_rgb(0.5, 0.0, 0.0);
                if (i==2 || i==3 || i==4 || i==8 || i==5 || i==10 || i==14 || i==18 || i==15 || i==22 || i==23 || i==24)
                {
                    pio_sm_put_blocking(pio, sm, color1);
                } else {
                    pio_sm_put_blocking(pio, sm, color2);
                }  
            }
        } else if (frame == 1)
        {
            for (int i = 0; i < NUM_PIXELS; i++) {
                uint32_t color1 = calcular_cor_rgb(0.0, 0.5, 0.5);
                if (i==0 || i==4 || i==5 || i==6 || i==7 || i==8 || i==9 || i==11 || i==13 || i==16 || i==18 || i==22)
                {
                    pio_sm_put_blocking(pio, sm, color1);
                } else {
                    pio_sm_put_blocking(pio, sm, color2);
                }  
            }
        }else if (frame == 2)
        {
            for (int i = 0; i < NUM_PIXELS; i++) {
                uint32_t color1 = calcular_cor_rgb(0.5, 0.5, 0.0);
                if (i==2 || i==6 || i==8 || i==11 || i==13 || i==15 || i==19 || i==20 || i==24)
                {
                    pio_sm_put_blocking(pio, sm, color1);
                } else {
                    pio_sm_put_blocking(pio, sm, color2);
                }  
            }
        } else if (frame == 3)
        {
            for (int i = 0; i < NUM_PIXELS; i++) {
                uint32_t color1 = calcular_cor_rgb(0.0, 0.0, 0.5);
                if (i==2 || i==7 || i==12 || i==17 || i==22)
                {
                    pio_sm_put_blocking(pio, sm, color1);
                } else {
                    pio_sm_put_blocking(pio, sm, color2);
                }  
            }
        } else
        {
            for (int i = 0; i < NUM_PIXELS; i++) {
                uint32_t color1 = calcular_cor_rgb(0.0, 0.5, 0.0);
                if (i==2 || i==3 || i==4 || i==8 || i==5 || i==10 || i==14 || i==18 || i==15 || i==22 || i==23 || i==24)
                {
                    pio_sm_put_blocking(pio, sm, color1);
                } else {
                    pio_sm_put_blocking(pio, sm, color2);
                }  
            }
        }
        sleep_ms(1000 / fps);
    }
}
void animacao_5(PIO pio, uint sm, int fps) {
    const int delay = 1000 / fps;  // Calcula o intervalo de tempo por frame em milissegundos
    const double pi = 3.14159265359;
    const int frames = 100;       // Número de frames para completar a animação
    const double step = 2 * pi / NUM_PIXELS; // Distância da onda entre os LEDs

    for (int frame = 0; frame < frames; frame++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            // Calcula uma onda senoidal para as cores
            double wave_position = frame * step + i * step;
            double r = (sin(wave_position) + 1) / 2;  // Normaliza de 0 a 1
            double g = (sin(wave_position + 2 * pi / 3) + 1) / 2;
            double b = (sin(wave_position + 4 * pi / 3) + 1) / 2;

            // Define a cor no LED i
            uint32_t color = calcular_cor_rgb(b, r, g);
            pio_sm_put_blocking(pio, sm, color);
        }

        // Pausa para respeitar o FPS
        sleep_ms(delay);
    }
}

// Mapear ações às teclas
// Mapeia e executa ações com base na tecla pressionada
// Parâmetros:
// - key: Caractere da tecla pressionada
// - pio: Instância do bloco PIO
// - sm: Máquina de estado usada para o controle
void executar_acao_tecla(char key, PIO pio, uint sm) {
    switch (key) {
        case '0': animacao_1(pio, sm, 10); break;
        // case '1': animacao_2(pio, sm, 10); break;
        case '2': animacao_3(pio, sm, 2); break;
        // case '3': animacao_4(pio, sm, 10); break;
         case '4': animacao_5(pio, sm, 10); break;
        // case '5': animacao_6(pio, sm, 10); break;
        // case '6': animacao_7(pio, sm, 10); break;
        case 'A': configurar_todos_leds(pio, sm, 0.0, 0.0, 0.0); break;
        case 'B': configurar_todos_leds(pio, sm, 0.0, 0.0, 1.0); break;
        case 'C': configurar_todos_leds(pio, sm, 0.8, 0.0, 0.0); break;
        case 'D': configurar_todos_leds(pio, sm, 0.0, 0.5, 0.0); break;
        case '#': configurar_todos_leds(pio, sm, 0.2, 0.2, 0.2); break;
    }
}

// Função principal
int main() {
    PIO pio = pio0;
    uint sm;

    // Inicializa hardware
    stdio_init_all();
    configurar_gpio_pio(pio, &sm, OUT_PIN);
    configurar_teclado();

    while (true) {
        char key = verificar_teclado();
        if (key) {
            executar_acao_tecla(key, pio, sm);
        }
        sleep_ms(100);
    }
}