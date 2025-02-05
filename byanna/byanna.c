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

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;


int main() {

    stdio_init_all();

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

restart:

    // char *text[] = {
    //     "   CONFIA    "};

    // int y = 0;
    // for (uint i = 0; i < count_of(text); i++)
    // {
    //     ssd1306_draw_string(ssd, 5, y, text[1]);
    //     y += 8;
    // }
    
    // render_on_display(ssd, &frame_area);

// Parte do código para exibir a linha no display (algoritmo de Bresenham)

    ssd1306_draw_line(ssd, 10, 10, 100, 50, true);
    render_on_display(ssd, &frame_area);


// Parte do código para exibir o bitmap no display

    const uint8_t bitmap_128x64[] = { 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 
0xff, 0xfb, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xff, 0xf1, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 
0xff, 0xf5, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xbf, 0x13, 0xfe, 0xff, 0xff, 0x03, 0x00, 0x00, 
0xbf, 0x00, 0xfe, 0xff, 0xff, 0x03, 0x00, 0x00, 0x1f, 0x00, 0xfe, 0xff, 0xff, 0x01, 0x00, 0x00, 
0x1f, 0x00, 0xc0, 0xff, 0xff, 0x01, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xff, 0xff, 0x01, 0x00, 0x00, 
0x0f, 0x00, 0x00, 0xfc, 0xff, 0x01, 0x00, 0x00, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0x01, 0x00, 0x00, 
0x0f, 0x00, 0x00, 0xc0, 0xff, 0x01, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x98, 0xff, 0x01, 0x00, 0x00, 
0x0f, 0x00, 0x00, 0x18, 0xfe, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 
0x0f, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 
0x0f, 0x00, 0x08, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x07, 0x00, 0x08, 0x00, 0xf0, 0x00, 0x00, 0x00, 
0x07, 0x00, 0x18, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x07, 0x00, 0x18, 0x0c, 0x60, 0x00, 0x00, 0x00, 
0x07, 0x00, 0x18, 0x0e, 0x40, 0x00, 0x00, 0x00, 0x03, 0x00, 0x9c, 0x0f, 0x00, 0x00, 0x00, 0x00, 
0x03, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xfc, 0x1f, 0x00, 0x00, 0x06, 0x00, 
0x03, 0x00, 0xf6, 0x0f, 0x00, 0x00, 0x06, 0x00, 0x01, 0xc0, 0xf2, 0x0f, 0x00, 0x00, 0x06, 0x00, 
0x01, 0xc0, 0x13, 0x2f, 0x00, 0x00, 0x07, 0x00, 0x03, 0x40, 0x03, 0x2f, 0x12, 0x80, 0x07, 0x00, 
0x03, 0xc0, 0x03, 0x6f, 0x3a, 0x00, 0x03, 0x00, 0x03, 0xc0, 0x03, 0x7f, 0x3b, 0x00, 0x00, 0x00, 
0x03, 0x80, 0x03, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x7f, 0x3f, 0x04, 0x04, 0x00, 
0x03, 0x80, 0x03, 0x77, 0x3f, 0x00, 0x04, 0x00, 0x03, 0x80, 0x09, 0x77, 0x3f, 0x00, 0x00, 0x00, 
0x03, 0x80, 0x09, 0x6f, 0x3f, 0x00, 0x00, 0x00, 0x03, 0x00, 0x89, 0x6f, 0xbf, 0x00, 0x02, 0x00, 
0x03, 0x00, 0x89, 0x1f, 0xbf, 0x80, 0x03, 0x00, 0x03, 0x00, 0x8b, 0x3f, 0x1e, 0xde, 0x01, 0x00, 
0x03, 0x00, 0xda, 0x7f, 0x9e, 0xff, 0x01, 0x00, 0x03, 0x00, 0xfe, 0xff, 0xcf, 0xff, 0x00, 0x00, 
0x03, 0x00, 0xfc, 0xff, 0xcf, 0xff, 0x00, 0x00, 0x03, 0x00, 0xfc, 0xff, 0xef, 0x7f, 0x00, 0x00, 
0x03, 0x00, 0xfc, 0xff, 0xf7, 0x3f, 0x00, 0x00, 0x07, 0x00, 0xfc, 0xff, 0xf7, 0x3f, 0x00, 0x00, 
0x0f, 0x00, 0xfc, 0xff, 0xfb, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0xf8, 0xff, 0xfd, 0x1f, 0x00, 0x00, 
0x0f, 0x00, 0xe0, 0xff, 0xfd, 0x0f, 0x00, 0x00, 0x0f, 0x00, 0x80, 0x31, 0xfc, 0x0f, 0x00, 0x00, 
0x1f, 0x00, 0x00, 0x80, 0xff, 0x0f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0xfe, 0x7f, 0x03, 0x00, 0x00, 
0x1f, 0x00, 0xe3, 0xfc, 0x7f, 0x00, 0x00, 0x00, 0x9f, 0x80, 0x7f, 0xfe, 0x7f, 0x00, 0x00, 0x00, 
0x9f, 0x80, 0x7f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xf0, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
0x7f, 0xfb, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0xff, 0xfc, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x09, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00
};

    ssd1306_t ssd_bm;
    ssd1306_init_bm(&ssd_bm, 128, 64, false, 0x3C, i2c1);
    ssd1306_config(&ssd_bm);

    ssd1306_draw_bitmap(&ssd_bm, bitmap_128x64);


    while(true) {
        sleep_ms(1000);
    }

    return 0;
}