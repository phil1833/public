/*
Sensor Hub/bridge Reference design.
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "hal_io.h"
#include "hal_rtos.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "platform.h"
#include "diag_task.h"
#include "usb_task.h"
#include "network_task.h"


static StaticTask_t DiagTaskTCB;
static StackType_t DiagTaskStack[ configMINIMAL_STACK_SIZE ];

static StaticTask_t UsbTaskTCB;
static StackType_t UsbTaskStack[ configMINIMAL_STACK_SIZE ];

static StaticTask_t NetworkTaskTCB;
static StackType_t NetworkTaskStack[ configMINIMAL_STACK_SIZE ];

int main(void)
{
	platform_init();
    msg_init();
	printf("Platform init done\r\n");

    ( void ) xTaskCreateStatic( diag_task,
                                "diag_task",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                configMAX_PRIORITIES - 1U,
                                &( DiagTaskStack[ 0 ] ),
                                &( DiagTaskTCB ) );


    ( void ) xTaskCreateStatic( usb_task,
                                "usb_task",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                configMAX_PRIORITIES - 1U,
                                &( UsbTaskStack[ 0 ] ),
                                &( UsbTaskTCB ) );

    ( void ) xTaskCreateStatic( network_task,
                                "network_task",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                configMAX_PRIORITIES - 1U,
                                &( NetworkTaskStack[ 0 ] ),
                                &( NetworkTaskTCB ) );                                

    /* Start the scheduler. */
    vTaskStartScheduler();

	while(1)
	{

	}
}