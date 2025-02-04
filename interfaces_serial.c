#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define BUTTON_A 5
#define BUTTON_B 6
#define BLUE_LED_PIN 11
#define GREEN_LED_PIN 12
#define DEBOUNCE_TIME 500

bool blue_led_on = false;
bool green_led_on = false;

void turn_on_led(bool g, bool b);
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

void turn_on_led(bool g, bool b) {
    gpio_put(GREEN_LED_PIN, g);
    gpio_put(BLUE_LED_PIN, b);
}

static void irq_handler(uint gpio, uint32_t events) {
    static volatile uint32_t last_time = 0; // Tempo da última pressão
    volatile uint32_t current_time = to_ms_since_boot(get_absolute_time()); // Tempo atual

    // Verifica se o botão foi pressionado muito rápido
    if (current_time - last_time < DEBOUNCE_TIME) return;

    last_time = current_time; // Atualiza o tempo da última pressão

    // Verifica se o botão pressionado foi o A
    if (gpio == BUTTON_A) {
        if (blue_led_on) { // Se o LED azul estiver ligado, desliga
            blue_led_on = false;
            turn_on_led(false, false);
            return;
        }
        // Se o LED azul estiver desligado, liga
        blue_led_on = true;
        turn_on_led(true, false);
        return;
    } 
    
    // Verifica se o botão pressionado foi o B
    if (green_led_on) { // Se o LED verde estiver ligado, desliga
        green_led_on = false;
        turn_on_led(false, false);
        return;
    }

    // Se o LED verde estiver desligado, liga
    green_led_on = true;
    turn_on_led(true, false);
}