#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

//Task Handlers
TaskHandle_t T1_handle;
TaskHandle_t T2_handle;
TaskHandle_t T3_handle;
//Handler for timer
TimerHandle_t pt_handle;
//Timer Id
void *const pt_timerid;

//Timer Function
void pt_timer_handler(TimerHandle_t xTimer)
{
    printf("Timer callback function fired from T3 task\n");
}

void T1_task(void *data)
{
    while(1)
    {
    printf("Realtimetask T1 created\n");
    printf("Realtimetask T1 ended\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void T2_task(void *data)
{
    while(1)
    {
    printf("Realtimetask T2 created\n");
    printf("Realtimetask T2 ended\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void T3_task(void *data)
{
    pt_handle = xTimerCreate("pt_timer", pdMS_TO_TICKS(10000),pdFALSE,pt_timerid,pt_timer_handler);
    //pdFALSE for firing only one time(one-shot timer)
    //pdTrue for repeated firing
    //start of timer
    xTimerStart(pt_handle,0);
    while(1)
    {
    printf("Realtimetask T3 created\n");
    printf("Realtimetask T3 ended\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    int i = 0;
    xTaskCreate(T1_task,"task1",2048,NULL,1,&T1_handle);
    xTaskCreate(T2_task,"task2",2048,NULL,2,&T2_handle);
    xTaskCreate(T3_task,"task3",2048,NULL,3,&T3_handle);
    while (1) {
        printf("[%d] Hello world!\n", i);
        i++;
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
