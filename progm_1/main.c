#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

//Task Handlers
TaskHandle_t T1_handle;
TaskHandle_t T2_handle;
TaskHandle_t T3_handle;
TaskHandle_t T4_handle;
TaskHandle_t T5_handle;
//msge queue handler
QueueHandle_t mque;

//Task-1
void T1_task(void *data)
{
    while(1)
    {
    printf("Realtimetask T1 created\n");
    printf("Realtimetask T1 ended\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

//Task-2
void T2_task(void *data)
{
    while(1)
    {
    printf("Realtimetask T2 created\n");
    printf("Realtimetask T2 ended\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

//Task-3
void T3_task(void *data)
{
    while(1)
    {
    printf("Realtimetask T3 created\n");
    printf("Realtimetask T3 ended\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

//Task-4 for queue
void T4_task(void *data)
{
    int var=0;
    while(1)
    {
        printf("T4 task started\n");
        var++;
        xQueueSend(mque,&var,0); //sending var to T5 task
        printf("T4 task sended data to T5\n");
        printf("T4 task ended\n");
        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}

//Task-5 fro queue
void T5_task(void *data)
{
    int buff;
    while(1)
    {
        printf("T5 task started\n");
        xQueueReceive(mque,&buff,0); //receiving var from T4 task
        printf("Data recieved from T4 task is stored in buff: %d\n",buff);
        printf("T5 task ended\n");
        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    int i = 0;
    mque = xQueueCreate(2, sizeof(int));
    xTaskCreate(T1_task,"task1",2048,NULL,1,&T1_handle);
    xTaskCreate(T2_task,"task2",2048,NULL,2,&T2_handle);
    xTaskCreate(T3_task,"task3",2048,NULL,3,&T3_handle);
    xTaskCreate(T4_task,"task4",2048,NULL,4,&T4_handle);
    xTaskCreate(T5_task,"task5",2048,NULL,5,&T5_handle);
    while (1) {
        printf("[%d] Hello world!\n", i);
        i++;
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
