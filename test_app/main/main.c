#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ebyte.h"

void app_main(void)
{
    xTaskCreate(dummy_task, "dummy_task", 1024, NULL, 10, NULL);
}