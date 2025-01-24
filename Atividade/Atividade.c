// FABIANA DE SOUZA SILVA
// 202421511720637

#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "pico/binary_info.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"

#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

#define BTN_A_PIN 5

int A_state = 0;    // Botão A está pressionado?

// Função para exibir mensagens no OLED
void exibir_mensagem(const char *linha1, const char *linha2, const char *linha3, uint8_t *ssd, struct render_area *frame_area) {
    memset(ssd, 0, ssd1306_buffer_length);  // Limpa o buffer do display

    // Exibe a primeira linha no topo
    if (linha1 != NULL) {
        ssd1306_draw_string(ssd, 10, 5, linha1); // Posição: x = 10, y = 5
    }

    // Exibe a segunda linha no meio
    if (linha2 != NULL) {
        ssd1306_draw_string(ssd, 10, 20, linha2); // Posição: x = 10, y = 20
    }

    // Exibe a terceira linha abaixo
    if (linha3 != NULL) {
        ssd1306_draw_string(ssd, 10, 35, linha3); // Posição: x = 10, y = 35
    }

    render_on_display(ssd, frame_area);  // Atualiza o display
}


void SinalAberto(uint8_t *ssd, struct render_area *frame_area) {
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 1);
    gpio_put(LED_B_PIN, 0);
    exibir_mensagem("SINAL ABERTO", "ATRAVESSAR ", "COM CUIDADO", ssd, frame_area);
}

void SinalAtencao(uint8_t *ssd, struct render_area *frame_area) {
    gpio_put(LED_R_PIN, 1);
    gpio_put(LED_G_PIN, 1);
    gpio_put(LED_B_PIN, 0);
    exibir_mensagem("SINAL ATENCAO", "PREPARE-SE", " ", ssd, frame_area);
}

void SinalFechado(uint8_t *ssd, struct render_area *frame_area) {
    gpio_put(LED_R_PIN, 1);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 0);
    exibir_mensagem("SINAL FECHADO", "AGUARDE", " ",ssd, frame_area);
}

int WaitWithRead(int timeMS) {
    for (int i = 0; i < timeMS; i = i + 100) {
        A_state = !gpio_get(BTN_A_PIN);
        if (A_state == 1) {
            return 1;
        }
        sleep_ms(100);
    }
    return 0;
}

int main() {

    stdio_init_all();

    // INICIANDO LEDS
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);

    // INICIANDO BOTÃO
    gpio_init(BTN_A_PIN);
    gpio_set_dir(BTN_A_PIN, GPIO_IN);
    gpio_pull_up(BTN_A_PIN);

    // Inicialização do I2C
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init();

    // Preparar área de renderização para o display
    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&frame_area);

    // Zera o display inteiro
    uint8_t ssd[ssd1306_buffer_length];
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    while (true) {

        SinalFechado(ssd, &frame_area);
        A_state = WaitWithRead(8000);   // espera com leitura do botäo

        if (A_state) {  // ALGUEM APERTOU O BOTAO - SAI DO SEMAFORO NORMAL
                        //SINAL AMARELO PARA OS CARROS POR 5s
            SinalAtencao(ssd, &frame_area);
            sleep_ms(5000);

            //SINAL VERMELHO PARA OS CARROS / VERDE PARA O PEDESTRE POR 10s
            SinalAberto(ssd, &frame_area);
            sleep_ms(10000);

        } else {  //NINGUEM APERTOU O BOTAO - CONTINUA NO SEMAFORO NORMAL
            SinalAtencao(ssd, &frame_area);
            sleep_ms(2000);

            //SINAL VERMELHO PARA OS CARROS / VERDE PARA O PEDESTRE POR 15s
            SinalAberto(ssd, &frame_area);
            sleep_ms(15000);
        }
    }

    return 0;
}
