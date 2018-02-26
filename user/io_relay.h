#ifndef __H_IO_RELAY__
#define __H_IO_RELAY__
#include "ets_sys.h"
#include "gpio.h"

void ICACHE_FLASH_ATTR io_relay_init();
void ICACHE_FLASH_ATTR io_relay_on();
void ICACHE_FLASH_ATTR io_relay_off();
#endif
