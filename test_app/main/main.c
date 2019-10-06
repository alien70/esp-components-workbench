#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ebyte.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#define LED (GPIO_NUM_2)

#define AUX (GPIO_NUM_18) // Purple
#define M0 (GPIO_NUM_19)  // Grey
#define M1 (GPIO_NUM_27)  // White

#define LORA_TXD (GPIO_NUM_17)
#define LORA_RXD (GPIO_NUM_16)
#define LORA_RTS (UART_PIN_NO_CHANGE)
#define LORA_CTS (UART_PIN_NO_CHANGE)

void led_task(void *argc)
{
    int level = 0;
    for (;;)
    {
        level = gpio_get_level(AUX);
        gpio_set_level(LED, level);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

/**
 * @brief ESP32 Workbench
 * 
 */
static void setup()
{
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    gpio_set_direction(M0, GPIO_MODE_OUTPUT);
    gpio_set_direction(M1, GPIO_MODE_OUTPUT);
    gpio_set_direction(AUX, GPIO_MODE_INPUT);

    set_m0_pin(M0);
    set_m1_pin(M1);
    set_aux_pin(AUX);

    set_txd_pin(LORA_TXD);
    set_rxd_pin(LORA_RXD);

    set_uart_baud_rate(_9600);
    set_parity(_8N1);
    set_uart_port(UART_NUM_2);
    
    ebyte_init();

    // set_uart_baud_rate(_115200);
    // write_parameters();
    xTaskCreate(led_task, "led_task", 1024, NULL, 10, NULL);
}

void app_main(void)
{
    setup();

    printf("\nModel: %02x\n", get_model());
    printf("Version: %02x\n", get_version());
    printf("Features: %02x\n\n", get_features());

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // ebyte_reset();
}