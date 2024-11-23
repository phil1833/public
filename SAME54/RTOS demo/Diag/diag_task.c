/*
 * diag_task.c
 *
 * Created: 11/5/2024 1:30:34 PM
 *  Author: plee
 */ 

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "stdio_io.h"

static SemaphoreHandle_t msg_mutex;



#define MAX_MSG_Q   100
#define MAX_LENGTH  50

struct content_t{
    uint16_t size;
    char buf[MAX_LENGTH];
};

struct msg_t{
    uint16_t total_cnt;
    uint16_t idx;
    uint16_t oidx;
    uint32_t MissingCnt;
    struct content_t content[MAX_MSG_Q];
};

struct msg_t msg;
char debug[MAX_LENGTH*2];

void DEBUG_MSG(const char *fmt, ...);
void print_debug();
void msg_init(void);
///////////////////////////////////////////////////////////////////

void MSG_OUT(const char *msg)
{
    stdio_io_write((uint8_t *)msg, strlen(msg));
}


void DEBUG_MSG(const char *fmt, ...)
{
    if(xSemaphoreTake(msg_mutex, ~0))
	{		
        va_list args;
        va_start(args,fmt);

        memset(debug, 0x00, MAX_LENGTH);
        vsprintf(debug, fmt, args);
        va_end(args);

        if(msg.total_cnt<MAX_MSG_Q){

            uint16_t size = strlen(debug);
            if(size >MAX_LENGTH){size = MAX_LENGTH;}
            memcpy(&msg.content[msg.idx].buf, debug, size);
            msg.total_cnt++;
            msg.idx =  (msg.idx+1)%MAX_MSG_Q;
        }
        else{
            msg.MissingCnt++;
        }

        if(msg.MissingCnt > 100){
            msg.MissingCnt = 0;
            MSG_OUT("Missing Count Over \r\n");
        }
		//print_debug();
        xSemaphoreGive(msg_mutex);
    }
}

void print_debug()
{
    uint16_t cnt = msg.total_cnt;
    for(int i=0; i<cnt; i++)
    {
        MSG_OUT((char *)msg.content[msg.oidx].buf);
        memset((char *)msg.content[msg.oidx].buf, 0x00, MAX_LENGTH);
        msg.oidx++;
        msg.oidx = (msg.oidx%MAX_MSG_Q);
        msg.total_cnt--;
    }
}

void msg_init(void)
{
    msg_mutex = xSemaphoreCreateMutex();
    msg.idx = 0;
    msg.oidx = 0;
    msg.MissingCnt = 0;
    msg.total_cnt = 0;
    for(int i=0; i<MAX_MSG_Q; i++)
    {
        msg.content[i].size = 0;        
    }
}

void diag_task(void *parameters)
{
    (void) parameters;

    for(;;)
    {   
		//printf("diag\r\n");
        if(xSemaphoreTake(msg_mutex, ~0))
		{
            print_debug();
            xSemaphoreGive(msg_mutex);
        }
    }
}