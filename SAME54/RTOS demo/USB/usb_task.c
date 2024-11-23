/*
 * usb_task.c
 *
 * Created: 11/5/2024 2:21:28 PM
 *  Author: plee
 */ 


#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "diag_task.h"

void usb_task(void *parameters)
{
    (void) parameters;

    for(;;)
    {   
        vTaskDelay(100);
        DEBUG_MSG("usb_task %d \r\n", 1);
		DEBUG_MSG("usb_task %d \r\n", 3);
		DEBUG_MSG("usb_task %d \r\n", 7);
    }
}