/*
 * platform.c
 *
 * Created: 11/5/2024 11:00:33 AM
 *  Author: plee
 */ 

#include "platform.h"
#include <hal_gpio.h>
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include "hal_usart_sync.h"
#include "stdio_io.h"

// SAME54 has 14 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7
#define GPIO_PIN_FUNCTION_I 8
#define GPIO_PIN_FUNCTION_J 9
#define GPIO_PIN_FUNCTION_K 10
#define GPIO_PIN_FUNCTION_L 11
#define GPIO_PIN_FUNCTION_M 12
#define GPIO_PIN_FUNCTION_N 13

#define PB24 GPIO(GPIO_PORTB, 24)
#define PB25 GPIO(GPIO_PORTB, 25)
#define LED0 GPIO(GPIO_PORTC, 18)

struct usart_sync_descriptor TARGET_IO;


void TARGET_IO_PORT_init(void)
{

	gpio_set_pin_function(PB25, PINMUX_PB25D_SERCOM2_PAD0);

	gpio_set_pin_function(PB24, PINMUX_PB24D_SERCOM2_PAD1);
}

void TARGET_IO_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM2_GCLK_ID_CORE, CONF_GCLK_SERCOM2_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM2_GCLK_ID_SLOW, CONF_GCLK_SERCOM2_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));

	hri_mclk_set_APBBMASK_SERCOM2_bit(MCLK);
}

void TARGET_IO_init(void)
{
	TARGET_IO_CLOCK_init();
	usart_sync_init(&TARGET_IO, SERCOM2, (void *)NULL);
	TARGET_IO_PORT_init();
}

void gpio_configuration()
{
	// Set pin direction to output
	gpio_set_pin_direction(LED0, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(LED0, GPIO_PIN_FUNCTION_OFF);    
	gpio_set_pin_level(LED0,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);    
}


void stdio_redirect_init(void)
{

	usart_sync_enable(&TARGET_IO);
	stdio_io_init(&TARGET_IO.io);
}

void platform_init()
{
    init_mcu();
    TARGET_IO_init();
    stdio_redirect_init();    
    gpio_configuration();

}
