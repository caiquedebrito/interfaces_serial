#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_A 5
#define BUTTON_B 6
#define BLUE_LED_PIN 11
#define GREEN_LED_PIN 12

static void irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    // Configuração do pino de LED azul
    gpio_init(BLUE_LED_PIN);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);

    // Configuração do pino de LED verde
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    // Configuração do pino de botão A
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Configuração do pino de botão B
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // Configuração do IRQ para o botão A
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &irq_handler);

    // Configuração do IRQ para o botão B
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &irq_handler);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}

static void irq_handler(uint gpio, uint32_t events) {

}