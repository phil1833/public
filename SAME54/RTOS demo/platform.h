/*
 * platform.h
 *
 * Created: 11/5/2024 11:00:19 AM
 *  Author: plee
 */ 


#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <hpl_init.h>

static inline void init_mcu(void)
{
	_init_chip();
}


void platform_init();


#endif /* PLATFORM_H_ */