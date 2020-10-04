#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

TaskHandle_t Task0;
TaskHandle_t Task1;
void taskPinToCore1(void *pvParameters){
    printf("Task running on Core : %d ",xPortGetCoreID());
    while (1)
    {
        printf("Start Core 1 ESP-IDF!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}
void taskPinToCore0(void *pvParameters){
    printf("Task running on Core : %d ",xPortGetCoreID());
    while(1){
        printf("Start Core 0 ESP-IDF!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    printf("Start Dual Core ESP-IDF!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU cores, WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    xTaskCreatePinnedToCore(taskPinToCore0,"Task0",2048,NULL,1,&Task0,0);
    xTaskCreatePinnedToCore(taskPinToCore1,"Task1",2048,NULL,1,&Task1,0);

}
