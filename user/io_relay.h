#ifndef __H_IO_RELAY__
#define __H_IO_RELAY__
#include "ets_sys.h"
#include "gpio.h"

#define PINFUNC FUNC_GPIO12
#define PINMUX PERIPHS_IO_MUX_MTDI_U
#define PINNUM 12//16 // Also named D8 on weemos d1 mini

void ICACHE_FLASH_ATTR io_relay_init();
void ICACHE_FLASH_ATTR io_relay_on();
void ICACHE_FLASH_ATTR io_relay_off();
#endif
