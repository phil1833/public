/*
 * network_task.c
 *
 * Created: 11/5/2024 2:23:50 PM
 *  Author: plee
 */ 

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "diag_task.h"

void network_task(void *parameters)
{
    (void) parameters;

    for(;;)
    {   
        //vTaskDelay(100);
        //DEBUG_MSG("network_task %d \r\n", 11);
		//DEBUG_MSG("network_task %d \r\n", 30);
		//DEBUG_MSG("network_task %d \r\n", 70);
    }
}