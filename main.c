#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

int main() {

    stdio_init_all();
    printf("ADC Example, measuring GPIO26\n");
    
    
    adc_init();
    adc_set_temp_sensor_enabled (true);
    adc_select_input(4);
    gpio_init (25);
    gpio_set_dir (25,true);
    
    while (1) {
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        const float conversion = 3.3f / (1 << 12);
        uint16_t resultado = adc_read();
        

        float T = 27 - (resultado * conversion - 0.706)/0.001721;


        printf("Raw value: 0x%03x, voltage: %.2f V, TEMP: %.2f °C\n", resultado, resultado * conversion, T);
        
        gpio_put(25, true);
        sleep_ms(100);
        gpio_put(25, false);
        sleep_ms(500);

    }
}